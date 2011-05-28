////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_7F578F96_35D0_4D8F_B5D7_4F131BF74058)
#define SHEOL_7F578F96_35D0_4D8F_B5D7_4F131BF74058

#include <sheol/config/branch_hints.hpp>
#include <sheol/config/manual_profiling.hpp>
#include <sheol/config/unused.hpp>
#include <sheol/config/visibility.hpp>
#include <sheol/config/inlining.hpp>

#if defined(SHEOL_SOURCE)
  #define SHEOL_EXPORT SHEOL_SYMBOL_EXPORT
#else
  #define SHEOL_EXPORT SHEOL_SYMBOL_IMPORT
#endif

// Including <cstddef> without C++0x support enabled offends GNU's standard
// library. These using statements won't cause problems if <cstddef> is
// included by the user, so they're harmless for compilers that don't use
// libstdc++
#include <stddef.h>
namespace std { using ::ptrdiff_t; using ::size_t; }

// Defining this macro will allow polymorphic types to be used with sheol
// allocators.
// #define SHEOL_NO_POLYMORPHIC_PROTECTION

#endif // SHEOL_7F578F96_35D0_4D8F_B5D7_4F131BF74058

