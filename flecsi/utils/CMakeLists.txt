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

set(utils_HEADERS
  array_ref.h
  bitfield.h
  check_sig.h
  check_types.h
  common.h
  const_string.h
  dimensioned_array.h
  doxygen_main.h
  dummy.h
  factory.h
  hash.h
  humble.h
  id.h
  index_space.h
  iterator.h
  reorder.h
  set_intersection.h
  static_for.h     detail/static_for.h
  static_list.h
  static_verify.h
  tuple_for_each.h detail/tuple_for_each.h
  tuple_visit.h    detail/tuple_visit.h
  tuple_zip.h      detail/tuple_zip.h
  zip.h            detail/zip.h
  TaskWrapper.h
  )

set(utils_SOURCES
  dummy.cc
  PARENT_SCOPE)


if (ENABLE_STATIC_CONTAINER)
set(utils_HEADERS 
   ${utils_HEADERS} 
   static_container/type_list.h
   static_container/meta_counter.h
   static_container/meta_list.h
   static_container/static_for.h
   )
endif (ENABLE_STATIC_CONTAINER)

if(FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")
set(utils_HEADERS 
   ${utils_HEADERS}
   mpi_legion_interoperability/legion_handshake.h
   mpi_legion_interoperability/mpi_legion_interop.h
   mpi_legion_interoperability/mpi_legion_data.h
   mpi_legion_interoperability/legion_arrays.h
   mpi_legion_interoperability/task_ids.h
   mpi_legion_interoperability/mapper.h
   )

set(utils_SOURCES
  ${utils_SOURCES}
  #mpi_legion_interoperability/mpi_legion_interop.cc
  PARENT_SCOPE)

endif(FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")

set(utils_HEADERS ${utils_HEADERS} PARENT_SCOPE)

cinch_add_unit(bitfield
  SOURCES test/bitfield.cc)
  
cinch_add_unit(check_sig
  SOURCES test/check_sig.cc)

cinch_add_unit(const_string
  SOURCES test/const_string.cc)

cinch_add_unit(factory
  SOURCES test/factory.cc)

cinch_add_unit(reorder
  SOURCES test/reorder.cc)

cinch_add_unit(zip
  SOURCES test/zip.cc)

cinch_add_unit(static_for
  SOURCES test/static_for.cc)

#cinch_add_unit(static_list
#  SOURCES test/static_list.cc)

cinch_add_unit(tuple_for_each
  SOURCES test/tuple_for_each.cc)

cinch_add_unit(tuple_visit
  SOURCES test/tuple_visit.cc)

cinch_add_unit(tuple_zip
  SOURCES test/tuple_zip.cc)
 
if(FLECSI_RUNTIME_MODEL STREQUAL "legion" OR FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")
cinch_add_unit(TaskWrapper
  SOURCES test/TaskWrapper.cc)
endif(FLECSI_RUNTIME_MODEL STREQUAL "legion" OR FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")

if (ENABLE_STATIC_CONTAINER)
cinch_add_unit(meta_container
  SOURCES test/meta_container.cc)
endif (ENABLE_STATIC_CONTAINER)

if(FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")
#cinch_add_unit(mpi_with_legion
#  SOURCES test/mpi_with_legion/mpi_with_legion.cc
#  POLICY MPILEGION)

#cinch_add_unit(more_complex_mpi_with_legion
#  SOURCES test/mpi_with_legion/more_complex_mpi_with_legion.cc
#  POLICY MPILEGION)

if (ENABLE_HYPRE)
cinch_add_unit(legion_with_Hypre
  SOURCES test/mpi_with_legion/legion_with_Hypre.cc
  POLICY MPILEGION
  LIBRARIES     ${HYPRE_LIBRARIES} )
endif (ENABLE_HYPRE)

#cinch_add_unit(mpi_legion_interop
#  SOURCES test/mpi_with_legion/mpi_legion_interop.cc
#  POLICY MPILEGION)

#cinch_add_unit(mpi_legion_data
#  SOURCES test/mpi_with_legion/mpi_legion_data.cc
#  POLICY MPILEGION)

endif(FLECSI_RUNTIME_MODEL STREQUAL "mpilegion")
#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
