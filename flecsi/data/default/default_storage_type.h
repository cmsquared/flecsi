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

#ifndef flecsi_default_storage_type_h
#define flecsi_default_storage_type_h

#include "flecsi/data/data_constants.h"

/*!
 * \file default_storage_policy.h
 * \authors bergen
 * \date Initial file creation: Oct 27, 2015
 */

namespace flecsi
{
namespace data_model
{
namespace default_storage_policy
{

  template<size_t ST, typename storage_t> struct storage_type_t {};

} // namespace default_storage_policy
} // namespace data_model
} // namespace flecsi

#endif // flecsi_default_storage_type_h

/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/
