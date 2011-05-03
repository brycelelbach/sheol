////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/memory/heapless_partition.hpp>

using sheol::memory::heapless_partition;

int main (void) {
  typedef heapless_partition<5, 0x1000> partition;

  // instantiate the partition
  void* p = 0;
  p = partition::allocate(); 

  return 0;
}

