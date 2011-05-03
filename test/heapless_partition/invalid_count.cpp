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
  // On most x86 systems, the (smallest) page size is 4 kilobytes.
  typedef heapless_partition<sizeof(T), 0x1000> partition;

  // Verify the initial state of the partition.
  SHEOL_TEST_EQ(partition::size(), 0U);
  SHEOL_TEST(partition::remaining() == partition::partition_size);
  
  // Make a bad allocation request.
  SHEOL_TEST_EQ(partition::allocate(0),
    reinterpret_cast<void*>(partition::invalid_count));
  
  // Make sure the bad allocation didn't mutate the partition data.
  SHEOL_TEST_EQ(partition::size(), 0U);
  SHEOL_TEST(partition::remaining() == partition::partition_size);
}

}

int main (void) {
  test<boost::uint8_t>();
  test<boost::uint16_t>();
  test<boost::uint32_t>();
  test<boost::uint64_t>();

  return sheol::report_errors();
}

