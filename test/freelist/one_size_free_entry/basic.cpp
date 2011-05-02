////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/cstdint.hpp>
#include <boost/detail/lightweight_test.hpp>

#include <edk/memory/one_size_free_entry.hpp>

using edk::memory::one_size_free_entry;

struct point {
  point (void): x(0), y(0), z(0) { }

  point (boost::uint64_t x_, boost::uint64_t y_, boost::uint64_t z_):
    x(x_), y(y_), z(z_) { }

  boost::uint64_t x;
  boost::uint64_t y;
  boost::uint64_t z;
};

int main (void) {
  typedef one_size_free_entry<point> osfe_type;

  {
    osfe_type osfe;
    
    BOOST_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0));
    BOOST_TEST_EQ(osfe.retrieve(), reinterpret_cast<point*>(0));
  }
  
  {
    osfe_type osfe(reinterpret_cast<point*>(0xbeef));
    
    BOOST_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0xbeef));
    BOOST_TEST_EQ(osfe.retrieve(), reinterpret_cast<point*>(0xbeef));

    osfe = osfe_type(reinterpret_cast<void*>(0xdead));

    BOOST_TEST_EQ(osfe.get(), reinterpret_cast<osfe_type*>(0xdead));
    BOOST_TEST_EQ(osfe.retrieve(), reinterpret_cast<point*>(0xdead));
  }

  return boost::report_errors();
}

