////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/cstdint.hpp>

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/heapless_pool.hpp>

using sheol::memory::heapless_pool;

namespace {

template <typename T>
void test (void) {
  // On most x86 systems, the (smallest) page size is 4 kilobytes.
  typedef heapless_pool<sizeof(T), 0x1000> pool;

  // Verify the initial state of the pool.
  SHEOL_TEST_EQ(pool::size(), 0U);
  SHEOL_TEST(pool::remaining() == pool::pool_size);
  
  // Make a bad allocation request.
  SHEOL_TEST_EQ(pool::allocate(0), reinterpret_cast<void*>(pool::invalid_count));
  
  // Make sure the bad allocation didn't mutate the pool data.
  SHEOL_TEST_EQ(pool::size(), 0U);
  SHEOL_TEST(pool::remaining() == pool::pool_size);
}

}

int main (void) {
  test<boost::uint8_t>();
  test<boost::uint16_t>();
  test<boost::uint32_t>();
  test<boost::uint64_t>();

  return sheol::report_errors();
}

