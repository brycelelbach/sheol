////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/memory/variable_size_free_entry.hpp>

using sheol::memory::variable_size_free_entry;

int main (void) {
  typedef variable_size_free_entry<void*[2]> entry_type;

  entry_type entry;

  entry_type::data_type* d;
  d = &entry.data;

  return 0;
}

