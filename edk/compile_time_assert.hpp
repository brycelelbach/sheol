////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_856C9F7E_3F43_426E_8AA5_7A19512C0527)
#define EDK_856C9F7E_3F43_426E_8AA5_7A19512C0527

// Allow to work around the MPL problem in BOOST_MPL_ASSERT_MSG generating
// multiple definition linker errors for certain compilers (VC++)
#if defined(EDK_NO_MPL_ASSERT_MSG)
  #include <boost/static_assert.hpp>
  #define EDK_COMPILE_TIME_ASSERT(Cond, Msg, Types) \
    BOOST_STATIC_ASSERT(Cond)                       \
    /**/
#else
  #include <boost/mpl/assert.hpp>
  #define EDK_COMPILE_TIME_ASSERT(Cond, Msg, Types) \
    BOOST_MPL_ASSERT_MSG(Cond, Msg, Types)          \
    /**/
#endif

#endif // EDK_856C9F7E_3F43_426E_8AA5_7A19512C0527

