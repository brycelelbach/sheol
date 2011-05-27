////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/variable_size_free_entry.hpp>

using sheol::memory::variable_size_free_entry;

template <typename T>
void test (void) {
  typedef variable_size_free_entry<T> vsfe_type;

  vsfe_type first(reinterpret_cast<T*>(0xcede), 18U),
            second(reinterpret_cast<T*>(0xcede), 7U);

  SHEOL_TEST(first != second); 

  first.reset(reinterpret_cast<T*>(0xcede), 18U);
  second.reset(reinterpret_cast<T*>(0xceed), 18U);

  SHEOL_TEST(first != second); 
  
  first.reset(reinterpret_cast<T*>(0xcede), 21U);
  second.reset(reinterpret_cast<T*>(0xceed), 18U);

  SHEOL_TEST(first != second); 
  
  first.reset(reinterpret_cast<T*>(0xcede), 18U);
  second.reset(reinterpret_cast<T*>(0xcede), 18U);

  SHEOL_TEST(first == second); 
}

int main (void) {
  test<void*[2]>(); 
  #if defined(SHEOL_X86_64_ARCHITECTURE)
    test<void*>();
  #endif

  return sheol::report_errors();
}

