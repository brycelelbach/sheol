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
  #include <boost/type_traits/is_pod.hpp>

  #include <sheol/adt/tagged_ptr.hpp>

  using sheol::adt::tagged_ptr;
  using sheol::adt::pod_tagged_ptr;
#endif

int main (void) {
  #if defined(SHEOL_X86_64_ARCHITECTURE)
//    SHEOL_TEST(!boost::is_pod<tagged_ptr<int> >::value);
//    SHEOL_TEST(boost::is_pod<pod_tagged_ptr<int> >::value);
    SHEOL_TEST(!__is_pod(tagged_ptr<int>));
    SHEOL_TEST(__is_pod(pod_tagged_ptr<int>));
  #endif

  return sheol::report_errors();
}

