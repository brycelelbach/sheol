////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_E2C99E09_8FFC_459F_BFFB_C0B1F733FBE8)
#define SHEOL_E2C99E09_8FFC_459F_BFFB_C0B1F733FBE8

#include <limits.h>

#include <sheol/config.hpp>

#include <boost/cstdint.hpp>
#include <boost/integer.hpp>

namespace sheol {

// If you get an error in this header, your platform doesn't have an integer
// type large enough to store a pointer; sheol needs such a type to function
// properly.
typedef boost::uint_t<sizeof(void*) * CHAR_BIT>::exact uintptr_t;
typedef boost::int_t<sizeof(void*) * CHAR_BIT>::exact intptr_t;

} // sheol

#endif // SHEOL_E2C99E09_8FFC_459F_BFFB_C0B1F733FBE8

