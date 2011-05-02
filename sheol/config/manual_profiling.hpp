////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_DBAC6251_2216_4880_8C0C_32FF17542EB6)
#define SHEOL_DBAC6251_2216_4880_8C0C_32FF17542EB6

#if defined(__GNUC__)
  #define SHEOL_SUPER_PURE  __attribute__((const)) 
  #define SHEOL_PURE        __attribute__((pure)) 
  #define SHEOL_HOT         __attribute__((hot)) 
  #define SHEOL_COLD        __attribute__((cold)) 
#else
  #define SHEOL_SUPER_PURE
  #define SHEOL_PURE
  #define SHEOL_HOT
  #define SHEOL_COLD
#endif

#endif // SHEOL_DBAC6251_2216_4880_8C0C_32FF17542EB6

