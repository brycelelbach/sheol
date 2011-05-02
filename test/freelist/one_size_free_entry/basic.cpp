////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/one_size_free_entry.hpp>

using sheol::memory::one_size_free_entry;

template <typename T>
void test (void) {
  typedef one_size_free_entry<T> osfe_type;

  {
    osfe_type osfe;
    
    SHEOL_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0));
    SHEOL_TEST_EQ(osfe.retrieve(), reinterpret_cast<T*>(0));
  }
  
  {
    osfe_type osfe(reinterpret_cast<T*>(0xbeef));

    SHEOL_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0xbeef));
    SHEOL_TEST_EQ(osfe.retrieve(), reinterpret_cast<T*>(0xbeef));

    osfe = osfe_type(reinterpret_cast<void*>(0xdead));

    SHEOL_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0xdead));
    SHEOL_TEST_EQ(osfe.retrieve(), reinterpret_cast<T*>(0xdead));

    osfe = reinterpret_cast<void*>(0xbeef);

    SHEOL_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0xbeef));
    SHEOL_TEST_EQ(osfe.retrieve(), reinterpret_cast<T*>(0xbeef));

    osfe.reset();

    SHEOL_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0));
    SHEOL_TEST_EQ(osfe.retrieve(), reinterpret_cast<T*>(0));

    osfe.reset(reinterpret_cast<T*>(0xaded));

    SHEOL_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0xaded));
    SHEOL_TEST_EQ(osfe.retrieve(), reinterpret_cast<T*>(0xaded));
  }
}

int main (void) {
  test<void*>();
  test<void*[2]>(); 

  return sheol::report_errors();
}

