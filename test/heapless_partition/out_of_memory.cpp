////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/cstdint.hpp>

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/heapless_partition.hpp>

using sheol::memory::heapless_partition;

namespace {

template <typename T>
void test (void) {
  typedef heapless_partition<sizeof(T), 0x1000> partition;
  
  { // Request an allocation that almost drains the partition. 
    void* ptr = partition::allocate(partition::partition_size - 1);
    SHEOL_TEST(ptr);
  }

  // Verify that there's space for one more object in the partition. 
  SHEOL_TEST(partition::size() == (partition::partition_size - 1));
  SHEOL_TEST_EQ(partition::remaining(), 1U);
 
  { // Request an array that the partition should fail to allocate.
    void* ptr = partition::allocate(2);
    SHEOL_TEST_EQ(ptr, reinterpret_cast<void*>(partition::out_of_memory));
  }
  
  // Make sure the bad allocation didn't mutate the partition data.
  SHEOL_TEST(partition::size() == (partition::partition_size - 1));
  SHEOL_TEST_EQ(partition::remaining(), 1U);
  
  { // Exhaust the partition.
    void* ptr = partition::allocate(1);
    SHEOL_TEST(ptr);
  }
 
  // Verify that the partition is exhausted.
  SHEOL_TEST(partition::size() == partition::partition_size);
  SHEOL_TEST_EQ(partition::remaining(), 0U);

  // Make a bad allocation request (asking for an object).
  SHEOL_TEST_EQ(partition::allocate(),
    reinterpret_cast<void*>(partition::out_of_memory));

  // Make sure the bad allocation didn't mutate the partition data.
  SHEOL_TEST(partition::size() == partition::partition_size);
  SHEOL_TEST_EQ(partition::remaining(), 0U);
  
  // Make a bad allocation request (asking for an array).
  SHEOL_TEST_EQ(partition::allocate(64),
    reinterpret_cast<void*>(partition::out_of_memory));

  // Make sure the bad allocation didn't mutate the partition data.
  SHEOL_TEST(partition::size() == partition::partition_size);
  SHEOL_TEST_EQ(partition::remaining(), 0U);
  
  // Make another bad allocation request (with an invalid count).
  SHEOL_TEST_EQ(partition::allocate(0),
    reinterpret_cast<void*>(partition::invalid_count));
  
  // Make sure the second bad allocation didn't mutate the partition data.
  SHEOL_TEST(partition::size() == partition::partition_size);
  SHEOL_TEST_EQ(partition::remaining(), 0U);
}

}

int main (void) {
  test<boost::uint8_t>();
  test<boost::uint16_t>();
  test<boost::uint32_t>();
  test<boost::uint64_t>();

  return sheol::report_errors();
}

