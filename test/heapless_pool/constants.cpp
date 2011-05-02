////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/heapless_pool.hpp>

using sheol::memory::heapless_pool;

int main (void) {
  typedef heapless_pool<1, 0x1000> byte_pool;  // Space for 0x1000 objects.
  typedef heapless_pool<2, 0x1000> word_pool;  // Space for 0x800 objects.
  typedef heapless_pool<4, 0x1000> dword_pool; // Space for 0x400 objects.
  typedef heapless_pool<8, 0x1000> qword_pool; // Space for 0x200 objects.

  SHEOL_TEST(byte_pool::object_size  == 1); 
  SHEOL_TEST(word_pool::object_size  == 2); 
  SHEOL_TEST(dword_pool::object_size == 4); 
  SHEOL_TEST(qword_pool::object_size == 8); 
  
  SHEOL_TEST(byte_pool::capacity  == 0x1000); 
  SHEOL_TEST(word_pool::capacity  == 0x1000); 
  SHEOL_TEST(dword_pool::capacity == 0x1000); 
  SHEOL_TEST(qword_pool::capacity == 0x1000); 
  
  SHEOL_TEST(byte_pool::pool_size  == 0x1000); 
  SHEOL_TEST(word_pool::pool_size  == 0x800); 
  SHEOL_TEST(dword_pool::pool_size == 0x400); 
  SHEOL_TEST(qword_pool::pool_size == 0x200); 
  
  SHEOL_TEST(byte_pool::size()  == 0); 
  SHEOL_TEST(word_pool::size()  == 0); 
  SHEOL_TEST(dword_pool::size() == 0); 
  SHEOL_TEST(qword_pool::size() == 0); 
  
  SHEOL_TEST(byte_pool::remaining()  == 0x1000); 
  SHEOL_TEST(word_pool::remaining()  == 0x800); 
  SHEOL_TEST(dword_pool::remaining() == 0x400); 
  SHEOL_TEST(qword_pool::remaining() == 0x200); 

  return sheol::report_errors();
}

