////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/adt/dynamic_array.hpp>

using sheol::adt::dynamic_array;

int main (void) {
  dynamic_array<std::size_t> a;

  // insertion
  for (dynamic_array<std::size_t>::size_type i = 0; i < 0x4000; ++i)
    a.push_back(i);

  SHEOL_TEST_EQ(a.size(), 0x4000U);

  // lookup
  for (dynamic_array<std::size_t>::size_type i = 0; i < 0x4000; ++i)
    SHEOL_TEST_EQ(a[i], i);

  // removal
  for (dynamic_array<std::size_t>::size_type i = 0; i < 0x4000; ++i)
    a.pop_back();
  
  SHEOL_TEST_EQ(a.size(), 0U);

  return sheol::report_errors();
}

