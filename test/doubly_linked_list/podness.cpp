////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
//#include <sheol/adt/doubly_linked_list.hpp>
#include <sheol/adt/pod_doubly_linked_list.hpp>

#include <boost/type_traits/is_pod.hpp>

//using sheol::adt::doubly_linked_list;
using sheol::adt::pod_doubly_linked_list;

int main (void) {
//  SHEOL_TEST(!boost::is_pod<doubly_linked_list<int> >::value);
  SHEOL_TEST(boost::is_pod<pod_doubly_linked_list<int> >::value);

  return sheol::report_errors();
}

