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
    dynamic_array<bool> a0, a1;

    a0.push_back(true);
    a0.push_back(false);
  
    a1.push_back(true);
    a1.push_back(true);

    SHEOL_TEST(a0 != a1);
  }
  
  {
    dynamic_array<bool> a0, a1;

    a0.push_back(false);
    a0.push_back(true);
  
    a1.push_back(true);
    a1.push_back(true);

    SHEOL_TEST(a0 != a1);
  }
  
  {
    dynamic_array<bool> a0, a1;

    a0.push_back(true);
    a0.push_back(true);
    a0.push_back(true);
  
    a1.push_back(true);
    a1.push_back(true);

    SHEOL_TEST(a0 != a1);
  }
  
  {
    dynamic_array<bool> a0, a1;

    a0.push_back(true);
    a0.push_back(true);
  
    a1.push_back(true);
    a1.push_back(true);
    a1.push_back(true);

    SHEOL_TEST(a0 != a1);
  }
  
  {
    dynamic_array<bool> a0, a1;

    a0.push_back(true);
    a0.push_back(true);
  
    a1.push_back(true);
    a1.push_back(true);

    SHEOL_TEST(a0 == a1);
  }

  return sheol::report_errors();
}

