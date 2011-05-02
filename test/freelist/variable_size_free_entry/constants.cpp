////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/cstdint.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <edk/memory/variable_size_free_entry.hpp>

using edk::memory::variable_size_free_entry;

template <typename T>
struct array_of_eight {
  T data[8];
};

int main (void) {
  typedef variable_size_free_entry<array_of_eight<boost::uint16_t> >
    vsfe_16_bytes;

  typedef variable_size_free_entry<array_of_eight<boost::uint32_t> >
    vsfe_32_bytes;

  typedef variable_size_free_entry<array_of_eight<boost::uint64_t> >
    vsfe_64_bytes;

  BOOST_TEST_EQ(std::size_t(vsfe_16_bytes::object_size), std::size_t(16));
  BOOST_TEST_EQ(std::size_t(vsfe_32_bytes::object_size), std::size_t(32));
  BOOST_TEST_EQ(std::size_t(vsfe_64_bytes::object_size), std::size_t(64));

  return boost::report_errors();
}
