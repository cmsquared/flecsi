#~----------------------------------------------------------------------------~#
#  @@@@@@@@  @@           @@@@@@   @@@@@@@@ @@
# /@@/////  /@@          @@////@@ @@////// /@@
# /@@       /@@  @@@@@  @@    // /@@       /@@
# /@@@@@@@  /@@ @@///@@/@@       /@@@@@@@@@/@@
# /@@////   /@@/@@@@@@@/@@       ////////@@/@@
# /@@       /@@/@@//// //@@    @@       /@@/@@
# /@@       @@@//@@@@@@ //@@@@@@  @@@@@@@@ /@@
# //       ///  //////   //////  ////////  // 
# 
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

set(execution_HEADERS
  context.h
  default_execution_policy.h
  legion_execution_policy.h
  mpi_execution_policy.h
  mpilegion_execution_policy.h
  task.h
  PARENT_SCOPE
)

#set(execution_SOURCES
#  PARENT_SCOPE
#)

cinch_add_unit(task
  SOURCES test/task.cc)

#if(FLECSI_RUNTIME_MODEL STREQUAL "legion" OR FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")
#cinch_add_unit(legion_flecsi_example
#  SOURCES test/legion.cc
#  POLICY LEGION)
#endif(FLECSI_RUNTIME_MODEL STREQUAL "legion" OR FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")

cinch_add_unit(mpi
  SOURCES test/mpi.cc
  POLICY MPI
  THREADS 2)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
