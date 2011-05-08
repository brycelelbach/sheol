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
  dynamic_array<int> a0, a1;

  // insertion
  a0.push_back(1);
  a0.push_back(2);
  a0.push_back(3);
  BOOST_TEST_EQ(a0.size(), 3U);
  BOOST_TEST_EQ(a1.size(), 0U);

  // copy
  a1 = a0;
  BOOST_TEST_EQ(a0.size(), 3U);
  BOOST_TEST_EQ(a1.size(), 3U);

  // clear first
  a0.clear();
  BOOST_TEST_EQ(a0.size(), 0U);
  BOOST_TEST_EQ(a1.size(), 3U);

  // lookup
  BOOST_TEST_EQ(a1[0], 1);
  BOOST_TEST_EQ(a1[1], 2);
  BOOST_TEST_EQ(a1[2], 3);

  // removal
  a1.pop_back();
  a1.pop_back();
  a1.pop_back();
  BOOST_TEST_EQ(a0.size(), 0U);
  BOOST_TEST_EQ(a1.size(), 0U);

  return boost::report_errors();
}

