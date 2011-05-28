////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2007-2011 Hartmut Kaiser
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_4987511F_CE54_4890_8A44_81356067E36E)
#define SHEOL_4987511F_CE54_4890_8A44_81356067E36E

#include <boost/config.hpp>

#if defined(BOOST_WINDOWS)
  #define SHEOL_SYMBOL_EXPORT      __declspec(dllexport)
  #define SHEOL_SYMBOL_IMPORT      __declspec(dllimport)
  #define SHEOL_SYMBOL_INTERNAL
#elif defined(__GNUC__)
  #define SHEOL_SYMBOL_EXPORT      __attribute__((visibility("default")))
  #define SHEOL_SYMBOL_IMPORT      __attribute__((visibility("default")))
  #define SHEOL_SYMBOL_INTERNAL    __attribute__((visibility("hidden")))
#else
  #define SHEOL_SYMBOL_EXPORT
  #define SHEOL_SYMBOL_IMPORT
  #define SHEOL_SYMBOL_INTERNAL
#endif

#endif // SHEOL_4987511F_CE54_4890_8A44_81356067E36E

