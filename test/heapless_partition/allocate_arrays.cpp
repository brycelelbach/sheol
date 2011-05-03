////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/scoped_array.hpp>
#include <boost/cstdint.hpp>

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/heapless_partition.hpp>

using sheol::memory::heapless_partition;

namespace {

template <typename T>
void test (void) {
  typedef heapless_partition<sizeof(T), 0x1000> partition;

  // A random number generator 
  boost::mt19937 rng;
  boost::uniform_int<T> dist; 

  T scratch;

  const typename partition::size_type partition_size
    = partition::partition_size / 2;

  // Allocate storage for the pointers with new.
  boost::scoped_array<T*> ptrs(new T*[partition_size]);

  for (typename partition::size_type i = 0; i < partition_size; ++i) {
    ptrs[i] = reinterpret_cast<T*>(partition::allocate(2));

    SHEOL_TEST(ptrs[i]);
    SHEOL_TEST(ptrs[i] != reinterpret_cast<void*>(partition::invalid_count));

    if (ptrs[i] && (ptrs[i] != reinterpret_cast<void*>
      (partition::invalid_count)))
    {
      (ptrs[i])[0] = dist(rng);
      (ptrs[i])[1] = dist(rng);
    }
    else {
      // Call the rng even on a bad allocation, so that the next iteration
      // isn't screwed up because of this failure.
      scratch = dist(rng);
      scratch = dist(rng);
    }
  }

  // Reset the random number generate
  rng.seed();

  // Check for corruption 
  for (typename partition::size_type i = 0; i < partition_size; ++i) {
    SHEOL_TEST(ptrs[i]);
    SHEOL_TEST(ptrs[i] != reinterpret_cast<void*>(partition::invalid_count));

    if (ptrs[i] && (ptrs[i] != reinterpret_cast<void*>
      (partition::invalid_count)))
    {
      // We cast here to avoid problems with iostream interpreting uint8_t as a
      // character.
      SHEOL_TEST_EQ(boost::uint64_t((ptrs[i])[0]), boost::uint64_t(dist(rng)));
      SHEOL_TEST_EQ(boost::uint64_t((ptrs[i])[1]), boost::uint64_t(dist(rng)));
    }
    else {
      // Call the rng anyways, so that the next iteration isn't screwed up. 
      scratch = dist(rng);
      scratch = dist(rng);
    }
  }
}

}

int main (void) {
  test<boost::uint8_t>();
  test<boost::uint16_t>();
  test<boost::uint32_t>();
  test<boost::uint64_t>();

  return sheol::report_errors();
}

