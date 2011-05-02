////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008-2009 Tim Blechmann, based on code by Cory Nelson
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/tagged_ptr.hpp>

using sheol::tagged_ptr;

int main (void) {
  #if defined(SHEOL_X86_64_ARCHITECTURE)
    int a(1), b(2);

    {
      tagged_ptr<int> i (&a, 0);
      tagged_ptr<int> j (&b, 1);

      i = j;

      SHEOL_TEST_EQ(i.get_ptr(), &b);
      SHEOL_TEST_EQ(i.get_tag(), 1);
    }

    {
      tagged_ptr<int> i (&a, 0);
      tagged_ptr<int> j (i);

      SHEOL_TEST_EQ(i.get_ptr(), j.get_ptr());
      SHEOL_TEST_EQ(i.get_tag(), j.get_tag());
    }
  #else
    SHEOL_TEST(true);
  #endif

  return sheol::report_errors();
}

