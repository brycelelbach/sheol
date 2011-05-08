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
  { 
    dynamic_array<int> a;

    // insertion
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    SHEOL_TEST_EQ(a.size(), 3U);

    // lookup
    SHEOL_TEST_EQ(a[0], 1);
    SHEOL_TEST_EQ(a[1], 2);
    SHEOL_TEST_EQ(a[2], 3);

    // removal
    a.pop_back();
    a.pop_back();
    a.pop_back();
    SHEOL_TEST_EQ(a.size(), 0U);
  }
  
  { 
    dynamic_array<int> a;

    // insertion
    for (dynamic_array<int>::size_type i = 0; i < 8; ++i)
      a.push_back(i + 1);

    SHEOL_TEST_EQ(a.size(), 8U);
    SHEOL_TEST_EQ(a.capacity(), 8U);

    a.push_back(9);
    SHEOL_TEST_EQ(a.size(), 9U);
    SHEOL_TEST_EQ(a.capacity(), 16U);

    // lookup
    for (dynamic_array<int>::size_type i = 0; i < 9; ++i)
      SHEOL_TEST_EQ(a[i], (i + 1));

    // removal
    a.clear();
    SHEOL_TEST_EQ(a.size(), 0U);
  }

  return sheol::report_errors();
}

