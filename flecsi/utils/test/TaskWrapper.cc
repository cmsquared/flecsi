/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2014 Los Alamos National Security, LLC
 * All rights reserved.
 *~-------------------------------------------------------------------------~~*/

#include <cinchtest.h>
#include "flecsi/utils/TaskWrapper.h"
#include "flecsi/execution/legion_execution_policy.h"

using namespace flecsi;

void example_task(int beta,double alpha,element_t i,state_accessor_t<double> a, state_accessor_t<int> b)
{

}

void example_task2(int beta,double alpha,bool what,state_accessor_t<double> a, state_accessor_t<int> b)
{

}

void example_task3(int beta)
{

}

TEST(TaskWrapper, TaskWrapper2) {

  /* Test Logic: See 'Google Test Macros' section below. */

	using TW = TaskWrapper<true,false,0,true,legion_execution_policy_t,std::function<decltype(example_task)>>;

	ASSERT_EQ(sizeof(TW::sArgT),sizeof(std::tuple<int,double>));

	using TW2 = TaskWrapper<true,false,0,true,legion_execution_policy_t,std::function<decltype(example_task2)>>;

	ASSERT_EQ(sizeof(TW2::sArgT),sizeof(std::tuple<int,double,bool>));

	using TW3 = TaskWrapper<true,false,0,true,legion_execution_policy_t,std::function<decltype(example_task3)>>;

	ASSERT_EQ(sizeof(TW3::sArgT),sizeof(std::tuple<int>));

} // TEST

# if 0 /* Remove guards to create more tests */
TEST(TaskWrapper, testname) {

  /* Test Logic: See 'Google Test Macros' section below. */

} // TEST

TEST(TaskWrapper, testname) {

  /* Test Logic: See 'Google Test Macros' section below. */

} // TEST
#endif // if 0

/*----------------------------------------------------------------------------*
 * Cinch test Macros
 *
 *  ==== I/O ====
 *  CINCH_CAPTURE()              : Insertion stream for capturing output.
 *                                 Captured output can be written or
 *                                 compared using the macros below.
 *
 *    EXAMPLE:
 *      CINCH_CAPTURE() << "My value equals: " << myvalue << std::endl;
 *
 *  CINCH_COMPARE_BLESSED(file); : Compare captured output with
 *                                 contents of a blessed file.
 *
 *  CINCH_WRITE(file);           : Write captured output to file.
 *
 * Google Test Macros
 *
 * Basic Assertions:
 *
 *  ==== Fatal ====             ==== Non-Fatal ====
 *  ASSERT_TRUE(condition);     EXPECT_TRUE(condition)
 *  ASSERT_FALSE(condition);    EXPECT_FALSE(condition)
 *
 * Binary Comparison:
 *
 *  ==== Fatal ====             ==== Non-Fatal ====
 *  ASSERT_EQ(val1, val2);      EXPECT_EQ(val1, val2)
 *  ASSERT_NE(val1, val2);      EXPECT_NE(val1, val2)
 *  ASSERT_LT(val1, val2);      EXPECT_LT(val1, val2)
 *  ASSERT_LE(val1, val2);      EXPECT_LE(val1, val2)
 *  ASSERT_GT(val1, val2);      EXPECT_GT(val1, val2)
 *  ASSERT_GE(val1, val2);      EXPECT_GE(val1, val2)
 *
 * String Comparison:
 *
 *  ==== Fatal ====                     ==== Non-Fatal ====
 *  ASSERT_STREQ(expected, actual);     EXPECT_STREQ(expected, actual)
 *  ASSERT_STRNE(expected, actual);     EXPECT_STRNE(expected, actual)
 *  ASSERT_STRCASEEQ(expected, actual); EXPECT_STRCASEEQ(expected, actual)
 *  ASSERT_STRCASENE(expected, actual); EXPECT_STRCASENE(expected, actual)
 *----------------------------------------------------------------------------*/

/*~------------------------------------------------------------------------~--*
 * Formatting options for vim.
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~------------------------------------------------------------------------~--*/
