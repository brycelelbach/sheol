////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2001 - 2003 John Maddock
//  Copyright (c) 2001 - 2003 Jens Maurer
//  Copyright (c) 2011        Bryce Lelbach
//
//  Most information based on the data collected by predef.sourceforge.net
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_B68C3117_9E30_4E79_8BF7_0F5A0A64A0AB)
#define SHEOL_B68C3117_9E30_4E79_8BF7_0F5A0A64A0AB

#include <cstddef>

// STLPort (stlport)
#if defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION)
  #define SHEOL_CXXSTDLIB "stlport"
  #define SHEOL_STLPORT_STDLIB 
#else
  #include <boost/config/no_tr1/utility.hpp>

// Comeau STL (como) 
#if defined(__LIBCOMO__)
  #define SHEOL_CXXSTDLIB "como"
  #define SHEOL_COMO_STDLIB 

// Apache/RogueWave (apache)
#elif defined(__STD_RWCOMPILER_H__) || defined(_RWSTD_VER)
  #define SHEOL_CXXSTDLIB "apache"
  #define SHEOL_APACHE_STDLIB 

// LLVM libc++ (llvm)
#elif defined(_LIBCPP_VERSION)
  #define SHEOL_CXXSTDLIB "llvm"
  #define SHEOL_LLVM_STDLIB 

// GNU libstdc++ (gnu)
#elif defined(__GLIBCPP__) || defined(__GLIBCXX__)
  #define SHEOL_CXXSTDLIB "gnu"
  #define SHEOL_GNU_STDLIB 

// SGI STL (sgi)
#elif defined(__STL_CONFIG_H)
  #define SHEOL_CXXSTDLIB "sgi"
  #define SHEOL_SGI_STDLIB 

// MSL (msl)
#elif defined(__MSL_CPP__)
  #define SHEOL_CXXSTDLIB "msl"
  #define SHEOL_MSL_STDLIB 

// IBM VACPP (ibm)
#elif defined(__IBMCPP__)
  #define SHEOL_CXXSTDLIB "ibm"
  #define SHEOL_IBM_STDLIB

// Modena C++ (modena) 
#elif defined(MSIPL_COMPILE_H)
  #define SHEOL_CXXSTDLIB "modena"
  #define SHEOL_MODENA_STDLIB

// Dinkumware (dinkumware)
#elif (defined(_YVALS) && !defined(__IBMCPP__)) || defined(_CPPLIB_VER)
  #define SHEOL_CXXSTDLIB "dinkumware"
  #define SHEOL_DINKUMWARE_STDLIB

#endif
#endif

#endif // SHEOL_B68C3117_9E30_4E79_8BF7_0F5A0A64A0AB

