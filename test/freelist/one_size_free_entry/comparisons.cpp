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

  osfe_type first(reinterpret_cast<T*>(0xcede)),
            second(reinterpret_cast<T*>(0xceed));

  SHEOL_TEST(first != second); 

  first.reset(reinterpret_cast<T*>(0xcede));
  second.reset(reinterpret_cast<T*>(0xcede));

  SHEOL_TEST(first == second); 
}

int main (void) {
  test<void*[2]>(); 
  #if defined(SHEOL_X86_64_ARCHITECTURE)
    test<void*>();
  #endif

  return sheol::report_errors();
}

