////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/cstdint.hpp>

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/one_size_free_entry.hpp>

using sheol::memory::one_size_free_entry;

template <typename T>
struct array_of_eight {
  T data[8];
};

int main (void) {
  typedef one_size_free_entry<array_of_eight<boost::uint16_t> >
    osfe_16_bytes;

  typedef one_size_free_entry<array_of_eight<boost::uint32_t> >
    osfe_32_bytes;

  typedef one_size_free_entry<array_of_eight<boost::uint64_t> >
    osfe_64_bytes;

  SHEOL_TEST_EQ(std::size_t(osfe_16_bytes::object_size), std::size_t(16));
  SHEOL_TEST_EQ(std::size_t(osfe_32_bytes::object_size), std::size_t(32));
  SHEOL_TEST_EQ(std::size_t(osfe_64_bytes::object_size), std::size_t(64));

  return sheol::report_errors();
}

