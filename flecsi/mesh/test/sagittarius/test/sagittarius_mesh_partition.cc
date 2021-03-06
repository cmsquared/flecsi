/*~-------------------------------------------------------------------------~~*
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
 *~-------------------------------------------------------------------------~~*/

#include <cinchtest.h>

#include <numeric>

#include "../sagittarius_mesh.h"
#include "sagittarius_fixture.h"

using namespace flecsi;
using namespace testing;

TEST_F(A_Sagittarius_Mesh_Partitioned_In_Two,
       number_of_vertex_partitions_should_be_2) {
  ASSERT_THAT(vertex_partitions, SizeIs(2));
}

TEST_F(A_Sagittarius_Mesh_Partitioned_In_Two,
       number_of_vertices_in_each_partition_should_be_4) {
  ASSERT_THAT(vertex_partitions[0].offset, SizeIs(4));
  ASSERT_THAT(vertex_partitions[1].offset, SizeIs(4));
}

TEST_F(A_Sagittarius_Mesh_Partitioned_In_Two, degree_of_vertices) {
  // FIXME: this test is still not intuitive enough.
  auto diff0 = std::vector<size_t>(vertex_partitions[0].offset.size());
  std::adjacent_difference(vertex_partitions[0].offset.begin(),
                           vertex_partitions[0].offset.end(),
                           diff0.begin());
  ASSERT_THAT(diff0, ElementsAre(0, 2, 3, 4));

  auto diff1 = std::vector<size_t>(vertex_partitions[1].offset.size());
  std::adjacent_difference(vertex_partitions[1].offset.begin(),
                           vertex_partitions[1].offset.end(),
                           diff1.begin());
  ASSERT_THAT(diff1, ElementsAre(0, 3, 2, 4));
}

TEST_F(A_Sagittarius_Mesh_Partitioned_In_Two,
       number_of_cell_partitions_should_be_2) {
  ASSERT_THAT(cell_partitions, SizeIs(2));
}

TEST_F(A_Sagittarius_Mesh_Partitioned_In_Two,
       number_of_cells_in_each_partition_should_be_2) {
  ASSERT_THAT(cell_partitions[0].offset, SizeIs(2));
  ASSERT_THAT(cell_partitions[1].offset, SizeIs(2));
}

TEST_F(A_Sagittarius_Mesh_Partitioned_In_Two,
       partition_is_a_range_of_entities_as_expected_by_ParMetis) {
  ASSERT_THAT(vertex_partitions[0].partition, ElementsAre(0, 4, 8));
  ASSERT_THAT(vertex_partitions[1].partition, ElementsAre(0, 4, 8));
  ASSERT_THAT(cell_partitions[0].partition, ElementsAre(0, 2, 4));
  ASSERT_THAT(cell_partitions[1].partition, ElementsAre(0, 2, 4));
}