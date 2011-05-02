////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/memory/one_size_free_entry.hpp>

using sheol::memory::one_size_free_entry;

struct value_type { void* p; };

int main (void) {
  typedef one_size_free_entry<value_type> osfe_type;

  value_type a;

  osfe_type const i(&a);
  osfe_type j(i);
  
  return 0; 
}

