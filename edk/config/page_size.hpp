////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_4F638AC5_CAC0_4BF3_BEF8_37793A4CD3BB)
#define EDK_4F638AC5_CAC0_4BF3_BEF8_37793A4CD3BB

// TODO: implement for other platforms
#if defined(__linux__)
  #include <sys/param.h>
  #define EDK_PAGE_SIZE EXEC_PAGESIZE
#endif

#endif // EDK_4F638AC5_CAC0_4BF3_BEF8_37793A4CD3BB

