////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/memory/variable_size_free_entry.hpp>

using sheol::memory::variable_size_free_entry;

struct value_type { void* p[2]; };

int main (void) {
  typedef variable_size_free_entry<value_type> vsfe_type;

  value_type a;

  vsfe_type i;

  i = vsfe_type(&a);
  
  return 0; 
}

