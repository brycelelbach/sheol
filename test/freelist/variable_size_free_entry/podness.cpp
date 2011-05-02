////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/type_traits/is_pod.hpp>

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/variable_size_free_entry.hpp>

using sheol::memory::variable_size_free_entry;
using sheol::memory::pod_variable_size_free_entry;

int main (void) {
  SHEOL_SANITY(!boost::is_pod<variable_size_free_entry<void*[2]> >::value);
  SHEOL_TEST(boost::is_pod<pod_variable_size_free_entry<void*[2]> >::value);
  #if defined(SHEOL_X86_64_ARCHITECTURE)
    SHEOL_SANITY(!boost::is_pod<variable_size_free_entry<void*> >::value);
    SHEOL_TEST(boost::is_pod<pod_variable_size_free_entry<void*> >::value);
  #endif

  return sheol::report_errors();
}

