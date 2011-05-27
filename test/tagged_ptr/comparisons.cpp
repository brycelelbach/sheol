////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008-2009 Tim Blechmann, based on code by Cory Nelson
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/detect/architecture.hpp>

#if defined(SHEOL_X86_64_ARCHITECTURE)
  #include <sheol/adt/tagged_ptr.hpp>

  using sheol::adt::tagged_ptr;
#endif

int main (void) {
  #if defined(SHEOL_X86_64_ARCHITECTURE)
    int a(1), b(2);

    {
      tagged_ptr<int> i(&a, 0);
      tagged_ptr<int> j(&a, 1);

      SHEOL_TEST(i != j);
    }

    {
      tagged_ptr<int> i(&a, 1);
      tagged_ptr<int> j(&b, 1);

      SHEOL_TEST(i != j);
    }

    {
      tagged_ptr<int> i(&a, 1);
      tagged_ptr<int> j(&b, 0);

      SHEOL_TEST(i != j);
    }

    {
      tagged_ptr<int> i(&a, 1);
      tagged_ptr<int> j(&a, 1);

      SHEOL_TEST(i == j);
    }
    
    {
      tagged_ptr<int> i;
      
      SHEOL_TEST(!i);

      i.set_ptr(&a);

      SHEOL_TEST(i);
    }
  #endif

  return sheol::report_errors();
}

