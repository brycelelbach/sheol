////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/adt/doubly_linked_list.hpp>

using sheol::adt::doubly_linked_list;

int main (void) {
  { 
    doubly_linked_list<int> a;

    // back insertion
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    //SHEOL_TEST_EQ(a.size(), 3U);

    // lookup
    doubly_linked_list<int>::const_iterator it = a.begin(),
                                            end = a.end();    
    SHEOL_TEST_EQ(*it, 1);
    SHEOL_TEST_EQ(*++it, 2);
    SHEOL_TEST_EQ(*++it, 3);
    SHEOL_TEST(++it == end);

    // back removal
    a.pop_back();
    a.pop_back();
    a.pop_back();
    //SHEOL_TEST_EQ(a.size(), 0U);
    SHEOL_TEST(a.empty());
  }
  
  { 
    doubly_linked_list<int> a;

    // front insertion
    a.push_front(1);
    a.push_front(2);
    a.push_front(3);
    //SHEOL_TEST_EQ(a.size(), 3U);

    // lookup
    doubly_linked_list<int>::const_iterator it = a.begin(),
                                            end = a.end();    
    SHEOL_TEST_EQ(*it, 3);
    SHEOL_TEST_EQ(*++it, 2);
    SHEOL_TEST_EQ(*++it, 1);
    SHEOL_TEST(++it == end);

    // front removal
    a.pop_front();
    a.pop_front();
    a.pop_front();
    //SHEOL_TEST_EQ(a.size(), 0U);
    SHEOL_TEST(a.empty());
  }
  
  { 
    doubly_linked_list<int> a;

    // back insertion
    for (doubly_linked_list<int>::size_type i = 0; i < 9; ++i)
      a.push_back(i);

    //SHEOL_TEST_EQ(a.size(), 9U);

    // lookup
    doubly_linked_list<int>::const_iterator it = a.begin(),
                                            end = a.end();    
    for (doubly_linked_list<int>::size_type i = 0; i < 9; ++i, ++it)
      SHEOL_TEST_EQ(*it, i);

    SHEOL_TEST(it == end);

    // removal
    a.clear();
    //SHEOL_TEST_EQ(a.size(), 0U);
    SHEOL_TEST(a.empty());
  }

  { 
    doubly_linked_list<int> a;

    // front insertion
    for (doubly_linked_list<int>::size_type i = 0; i < 9; ++i)
      a.push_front(i);

    //SHEOL_TEST_EQ(a.size(), 9U);

    // lookup
    doubly_linked_list<int>::const_iterator it = a.begin(),
                                            end = a.end();    
    for (doubly_linked_list<int>::size_type i = 9; i != 0; --i, ++it)
      SHEOL_TEST_EQ(*it, i - 1);

    SHEOL_SANITY(it == end);

    // removal
    a.clear();
    //SHEOL_TEST_EQ(a.size(), 0U);
    SHEOL_TEST(a.empty());
  }

  return sheol::report_errors();
}

