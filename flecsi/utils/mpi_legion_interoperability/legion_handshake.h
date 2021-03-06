/*~--------------------------------------------------------------------------~*
 *  @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
 * /@@/////  /@@          @@////@@ @@////// /@@
 * /@@       /@@  @@@@@  @@    // /@@       /@@
 * /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
 * /@@////   /@@/@@@@@@@/@@       ////////@@/@@
 * /@@       /@@/@@//// //@@    @@       /@@/@@
 * /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
 * //       ///  //////   //////  ////////  // 
 * 
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~--------------------------------------------------------------------------~*/
#ifndef LEGION_HANDSHAKE_HPP
#define LEGION_HANDSHAKE_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <mutex>
#include <condition_variable>

#include "mpi.h"

#include "legion.h"
#include "realm.h"

// the main idea of the handshake is change from MPI to Legion and vice
// versa  through locking/unlocking threads's mutex
// the order should be like next
// 
// handshake->legion_init();
// .. call legion tasks
// handshake->ext_wait_on_legion();
// handshake->ext_init();
// handshake->legion_handoff_to_ext();
// .. do some MPI staff
// handshake.legion_wait_on_ext();
// handshake->ext_handoff_to_legion();
// .. do some legion execution
// handshake->ext_wait_on_legion();
// handshake->legion_handoff_to_ext();

#define CHECK_PTHREAD(cmd) do { \
  int ret = (cmd); \
  if(ret != 0) { \
    fprintf(stderr, "PTHREAD: %s = %d (%s)\n", #cmd, ret, strerror(ret)); \
    exit(1); \
  } \
} while(0)

namespace flecsi
{
namespace mpilegion
{

class ExtLegionHandshake {
public:
  enum { IN_EXT, IN_LEGION };

  typedef Realm::UserEvent UserEvent;

  ExtLegionHandshake(
       int init_state, 
       int _ext_queue_depth = 1, 
       int _legion_queue_depth = 1);

  ~ExtLegionHandshake(void){delete ext_queue; delete legion_queue;};

  void ext_init(void);

  void legion_init(void);

  void ext_handoff_to_legion(void);

  void ext_wait_on_legion(void);

  void legion_handoff_to_ext(void);
  
  void legion_wait_on_ext(void);
protected:
  int state, ext_queue_depth, legion_queue_depth, ext_count, legion_count;
  UserEvent *ext_queue, *legion_queue;
  pthread_mutex_t sync_mutex;
  pthread_cond_t sync_cond;
};

ExtLegionHandshake::ExtLegionHandshake(
  int init_state, 
  int _ext_queue_depth,
  int _legion_queue_depth)
  : state(init_state), 
  ext_queue_depth(_ext_queue_depth),
  legion_queue_depth(_legion_queue_depth),
  ext_count(0),
  legion_count(0)
{
  pthread_mutex_init(&sync_mutex, 0);
  pthread_cond_init(&sync_cond, 0);
#ifndef SHARED_LOWLEVEL
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  printf("handshake %p created on rank %d\n", this, rank);
#endif
}

void ExtLegionHandshake::ext_init(void)
{
 CHECK_PTHREAD( pthread_mutex_lock(&sync_mutex) );

  //printf("handshake %p: ext init - counts = L=%d, E=%d\n",
  //    this, legion_count, ext_count);

  ext_count++;

  if(legion_count == 0) {
    // no legion threads have arrived, so sleep until one does
    //printf("ext sleeping...\n");
    CHECK_PTHREAD( pthread_cond_wait(&sync_cond, &sync_mutex) );
    //printf("ext awake...\n");
  } else {
    // if we were the first ext thread to arrive, wake the legion thread(s)
    if(ext_count == 1) {
      //printf("signalling\n");
      CHECK_PTHREAD( pthread_cond_broadcast(&sync_cond) );
    }
  }

  CHECK_PTHREAD( pthread_mutex_unlock(&sync_mutex) ); 
}

void ExtLegionHandshake::legion_init(void)
{
 CHECK_PTHREAD( pthread_mutex_lock(&sync_mutex) );

  if(!legion_count) {
    // first legion thread creates the events/queues
    // for later synchronization, then arrive at initialization barrier
    ext_queue = new UserEvent[ext_queue_depth];
    for(int i = 0; i < ext_queue_depth; i++)
      ext_queue[i] = ((i || (state == IN_EXT)) ?
                        UserEvent::create_user_event() :
                        UserEvent());

    legion_queue = new UserEvent[legion_queue_depth];
    for(int i = 0; i < legion_queue_depth; i++)
      legion_queue[i] = ((i || (state == IN_LEGION)) ?
                           UserEvent::create_user_event() :
                           UserEvent());
  }

  //printf("handshake %p: legion init - counts = L=%d, E=%d\n",
  // this, legion_count, ext_count);
  legion_count++;

  if(ext_count == 0) {
    // no external threads have arrived, so sleep until one does
    //printf("legion sleeping...\n");
    CHECK_PTHREAD( pthread_cond_wait(&sync_cond, &sync_mutex) );
    //printf("legion awake...\n");
  } else {
    // if we were the first legion thread to arrive, wake the ext thread(s)
    if(legion_count == 1) {
      //printf("signalling\n");
      CHECK_PTHREAD( pthread_cond_broadcast(&sync_cond) );
    }
  }

  CHECK_PTHREAD( pthread_mutex_unlock(&sync_mutex) );
}

void ExtLegionHandshake::ext_handoff_to_legion(void)
{
  assert(state == IN_EXT);

  // we'll trigger the first event in the ext queue, but first, 
  // create a new event for the legion queue
  //  and shift it onto the end
  assert(legion_queue[0].has_triggered());
  for(int i = 1; i < legion_queue_depth; i++)
    legion_queue[i - 1] = legion_queue[i];
  legion_queue[legion_queue_depth - 1] = UserEvent::create_user_event();

  state = IN_LEGION;
  ext_queue[0].trigger();
}

void ExtLegionHandshake::ext_wait_on_legion(void)
{
  legion_queue[0].external_wait();
  assert(state == IN_EXT);
}

void ExtLegionHandshake::legion_handoff_to_ext(void)
{
  assert(state == IN_LEGION);

  // we'll trigger the first event in the ext queue, but first, 
  // create a new event for the legion queue
  //  and shift it onto the end
  assert(ext_queue[0].has_triggered());
  for(int i = 1; i < ext_queue_depth; i++)
    ext_queue[i - 1] = ext_queue[i];
  ext_queue[ext_queue_depth - 1] = UserEvent::create_user_event();

  state = IN_EXT;
  legion_queue[0].trigger();
}

void ExtLegionHandshake::legion_wait_on_ext(void)
{
  ext_queue[0].wait();
  assert(state == IN_LEGION);
}


}//end namespace mpilegion

}//end namespace flecsi

#endif
/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/

