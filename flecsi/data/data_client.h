/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2015 Los Alamos National Security, LLC
 * All rights reserved.
 *~--------------------------------------------------------------------------~*/

#ifndef flecsi_data_client_h
#define flecsi_data_client_h

#include "flecsi/utils/common.h"
#include "flecsi/data/data_constants.h"

/*!
 * \file data_client.h
 * \authors bergen
 * \date Initial file creation: Mar 23, 2016
 */

namespace flecsi {

/*!
  \class data_client_t data_client.h
  \brief data_client_t provides...
 */
class data_client_t
{
public:

  //! Default constructor
  data_client_t() : id_(unique_id_t<size_t>::instance().next()) {}

  //! Copy constructor (disabled)
  data_client_t(const data_client_t &) = delete;

  //! Assignment operator (disabled)
  data_client_t & operator = (const data_client_t &) = delete;

  // Allow move operations
  data_client_t(data_client_t && o) = default;
  data_client_t & operator=(data_client_t && o) = default;

  //! Destructor
  virtual ~data_client_t() {}

  /*!
    Return a unique runtime identifier for namespace access to the
    data manager.
   */
  uintptr_t runtime_id() const {
    return reinterpret_cast<uintptr_t>(this+id_);
  } // runtime_id

private:

  size_t id_;

}; // class data_client_t

} // namespace flecsi

#endif // flecsi_data_client_h

/*~-------------------------------------------------------------------------~-*
 * Formatting options for vim.
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/
