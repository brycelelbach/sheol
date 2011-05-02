////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/detail/lightweight_test.hpp>

#include <edk/memory/variable_size_free_entry.hpp>

using edk::memory::variable_size_free_entry;

template <typename T>
void test (void) {
  typedef variable_size_free_entry<T> vsfe_type;

  {
    vsfe_type vsfe;
    
    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0));
    BOOST_TEST_EQ(vsfe.size(), 1U);
  }
  
  {
    vsfe_type vsfe(reinterpret_cast<T*>(0xbeef), 6U);

    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0xbeef));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0xbeef));
    BOOST_TEST_EQ(vsfe.size(), 6U);

    vsfe = vsfe_type(reinterpret_cast<void*>(0xdead), 16U);

    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0xdead));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0xdead));
    BOOST_TEST_EQ(vsfe.size(), 16U);

    vsfe = reinterpret_cast<vsfe_type*>(0xaded);

    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0xaded));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0xaded));
    BOOST_TEST_EQ(vsfe.size(), 1U);

    vsfe.size(5U);

    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0xaded));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0xaded));
    BOOST_TEST_EQ(vsfe.size(), 5U);

    vsfe.reset();

    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0));
    BOOST_TEST_EQ(vsfe.size(), 1U);

    vsfe.reset(reinterpret_cast<T*>(0xff), 8U);

    BOOST_TEST_EQ(vsfe.get(), reinterpret_cast<vsfe_type*>(0xff));
    BOOST_TEST_EQ(vsfe.retrieve(), reinterpret_cast<T*>(0xff));
    BOOST_TEST_EQ(vsfe.size(), 8U);
  }
}

int main (void) {
  test<void*[2]>(); 
  #if defined(BOOST_DETECT_X86_64_ARCHITECTURE)
    test<void*>();
  #endif

  return boost::report_errors();
}

