////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/one_size_freelist.hpp>

using sheol::memory::one_size_freelist;

template <std::size_t ObjectSize>
void test (void) {
  typedef one_size_freelist<ObjectSize> osfl_type;

  osfl_type osfl;
}

int main (void) {
  test<sizeof(void*)>();
  test<sizeof(void*[2])>(); 

  return sheol::report_errors();
}

