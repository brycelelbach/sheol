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
  typedef heapless_pool<sizeof(T), 0x1000> pool;
  
  { // Request an allocation that almost drains the pool. 
    void* ptr = pool::allocate(pool::pool_size - 1);
    SHEOL_TEST(ptr);
  }

  // Verify that there's space for one more object in the pool. 
  SHEOL_TEST(pool::size() == (pool::pool_size - 1));
  SHEOL_TEST_EQ(pool::remaining(), 1U);
 
  { // Request an array that the pool should fail to allocate.
    void* ptr = pool::allocate(2);
    SHEOL_TEST_EQ(ptr, reinterpret_cast<void*>(pool::out_of_memory));
  }
  
  // Make sure the bad allocation didn't mutate the pool data.
  SHEOL_TEST(pool::size() == (pool::pool_size - 1));
  SHEOL_TEST_EQ(pool::remaining(), 1U);
  
  { // Exhaust the pool.
    void* ptr = pool::allocate(1);
    SHEOL_TEST(ptr);
  }
 
  // Verify that the pool is exhausted.
  SHEOL_TEST(pool::size() == pool::pool_size);
  SHEOL_TEST_EQ(pool::remaining(), 0U);

  // Make a bad allocation request (asking for an object).
  SHEOL_TEST_EQ(pool::allocate(),
    reinterpret_cast<void*>(pool::out_of_memory));

  // Make sure the bad allocation didn't mutate the pool data.
  SHEOL_TEST(pool::size() == pool::pool_size);
  SHEOL_TEST_EQ(pool::remaining(), 0U);
  
  // Make a bad allocation request (asking for an array).
  SHEOL_TEST_EQ(pool::allocate(64),
    reinterpret_cast<void*>(pool::out_of_memory));

  // Make sure the bad allocation didn't mutate the pool data.
  SHEOL_TEST(pool::size() == pool::pool_size);
  SHEOL_TEST_EQ(pool::remaining(), 0U);
  
  // Make another bad allocation request (with an invalid count).
  SHEOL_TEST_EQ(pool::allocate(0), reinterpret_cast<void*>(pool::invalid_count));
  
  // Make sure the second bad allocation didn't mutate the pool data.
  SHEOL_TEST(pool::size() == pool::pool_size);
  SHEOL_TEST_EQ(pool::remaining(), 0U);
}

}

int main (void) {
  test<boost::uint8_t>();
  test<boost::uint16_t>();
  test<boost::uint32_t>();
  test<boost::uint64_t>();

  return sheol::report_errors();
}

