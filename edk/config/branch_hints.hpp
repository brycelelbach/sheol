////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//  Copyright (C) 2007, 2008 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_1DC28EC1_705B_4754_B33B_56D8D928B33D)
#define EDK_1DC28EC1_705B_4754_B33B_56D8D928B33D

#if defined(__GNUC__)
  #define EDK_LIKELY(expr)    __builtin_expect(expr, true)
  #define EDK_UNLIKELY(expr)  __builtin_expect(expr, false)
#else
  #define EDK_LIKELY(expr)    expr
  #define EDK_UNLIKELY(expr)  expr 
#endif

#endif // EDK_1DC28EC1_705B_4754_B33B_56D8D928B33D 

