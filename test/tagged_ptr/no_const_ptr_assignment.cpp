////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/detect/architecture.hpp>

#if defined(SHEOL_X86_64_ARCHITECTURE)
  #include <sheol/tagged_ptr.hpp>

  using sheol::tagged_ptr;
#endif


int main (void) {
  #if defined(SHEOL_X86_64_ARCHITECTURE)
    int a(1);
    int* const b = &a;

    tagged_ptr<int> i;
    i = &b;
  #else
    #error Architecture not supported.
  #endif

  return 0;
}

