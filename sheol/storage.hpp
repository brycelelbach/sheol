////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_0884BFFA_30C7_41DC_9723_594E0468F5E2)
#define SHEOL_0884BFFA_30C7_41DC_9723_594E0468F5E2

#include <sheol/cstdint.hpp>

namespace sheol {

template <std::size_t Bytes>
struct storage {
  typedef boost::uint8_t type [Bytes]; 
};

} // sheol

#endif // SHEOL_0884BFFA_30C7_41DC_9723_594E0468F5E2

