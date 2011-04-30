////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <boost/detail/lightweight_test.hpp>

#include <edk/memory/heapless_pool.hpp>

using edk::memory::heapless_pool;

int main (void) {
  // On most x86 systems, the (smallest) page size is 4 kilobytes.

  typedef heapless_pool<1, 0x1000> byte_pool;  // Space for 0x1000 objects.
  typedef heapless_pool<2, 0x1000> word_pool;  // Space for 0x800 objects.
  typedef heapless_pool<4, 0x1000> dword_pool; // Space for 0x400 objects.
  typedef heapless_pool<8, 0x1000> qword_pool; // Space for 0x200 objects.

  BOOST_TEST(byte_pool::object_size  == 1); 
  BOOST_TEST(word_pool::object_size  == 2); 
  BOOST_TEST(dword_pool::object_size == 4); 
  BOOST_TEST(qword_pool::object_size == 8); 
  
  BOOST_TEST(byte_pool::capacity  == 0x1000); 
  BOOST_TEST(word_pool::capacity  == 0x1000); 
  BOOST_TEST(dword_pool::capacity == 0x1000); 
  BOOST_TEST(qword_pool::capacity == 0x1000); 
  
  BOOST_TEST(byte_pool::pool_size  == 0x1000); 
  BOOST_TEST(word_pool::pool_size  == 0x800); 
  BOOST_TEST(dword_pool::pool_size == 0x400); 
  BOOST_TEST(qword_pool::pool_size == 0x200); 
  
  BOOST_TEST(byte_pool::size()  == 0); 
  BOOST_TEST(word_pool::size()  == 0); 
  BOOST_TEST(dword_pool::size() == 0); 
  BOOST_TEST(qword_pool::size() == 0); 
  
  BOOST_TEST(byte_pool::remaining()  == 0x1000); 
  BOOST_TEST(word_pool::remaining()  == 0x800); 
  BOOST_TEST(dword_pool::remaining() == 0x400); 
  BOOST_TEST(qword_pool::remaining() == 0x200); 

  return boost::report_errors();
}

