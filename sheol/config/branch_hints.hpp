////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_1DC28EC1_705B_4754_B33B_56D8D928B33D)
#define SHEOL_1DC28EC1_705B_4754_B33B_56D8D928B33D

#if defined(__GNUC__)
  #define SHEOL_LIKELY(expr)    __builtin_expect(expr, true)
  #define SHEOL_UNLIKELY(expr)  __builtin_expect(expr, false)
#else
  #define SHEOL_LIKELY(expr)    expr
  #define SHEOL_UNLIKELY(expr)  expr 
#endif

#endif // SHEOL_1DC28EC1_705B_4754_B33B_56D8D928B33D 

