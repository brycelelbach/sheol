////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/cstdint.hpp>

#include <edk/memory/variable_size_free_entry.hpp>

using edk::memory::variable_size_free_entry;

int main (void) {
  typedef variable_size_free_entry<boost::uint8_t> byte_entry;

  byte_entry entry;

  return 0;
}

