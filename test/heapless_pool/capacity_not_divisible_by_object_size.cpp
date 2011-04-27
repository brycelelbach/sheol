////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <edk/memory/heapless_pool.hpp>

using edk::memory::heapless_pool;

int main (void) {
  typedef heapless_pool<5, 0x1000> pool;

  // instantiate the pool
  void* p = 0;
  p = pool::allocate(); 

  return 0;
}

