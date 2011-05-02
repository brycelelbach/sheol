////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/memory/heapless_pool.hpp>

using sheol::memory::heapless_pool;

int main (void) {
  typedef heapless_pool<64, 8> pool;

  // instantiate the pool
  void* p = 0;
  p = pool::allocate(); 

  return 0;
}

