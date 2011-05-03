////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#include <sheol/lightweight_test.hpp>
#include <sheol/memory/heapless_partition.hpp>

using sheol::memory::heapless_partition;

int main (void) {
  typedef heapless_partition<1, 0x1000> byte_part;  // Space for 0x1000 objects.
  typedef heapless_partition<2, 0x1000> word_part;  // Space for 0x800 objects.
  typedef heapless_partition<4, 0x1000> dword_part; // Space for 0x400 objects.
  typedef heapless_partition<8, 0x1000> qword_part; // Space for 0x200 objects.

  SHEOL_TEST(byte_part::object_size  == 1); 
  SHEOL_TEST(word_part::object_size  == 2); 
  SHEOL_TEST(dword_part::object_size == 4); 
  SHEOL_TEST(qword_part::object_size == 8); 
  
  SHEOL_TEST(byte_part::capacity  == 0x1000); 
  SHEOL_TEST(word_part::capacity  == 0x1000); 
  SHEOL_TEST(dword_part::capacity == 0x1000); 
  SHEOL_TEST(qword_part::capacity == 0x1000); 
  
  SHEOL_TEST(byte_part::partition_size  == 0x1000); 
  SHEOL_TEST(word_part::partition_size  == 0x800); 
  SHEOL_TEST(dword_part::partition_size == 0x400); 
  SHEOL_TEST(qword_part::partition_size == 0x200); 
  
  SHEOL_TEST(byte_part::size()  == 0); 
  SHEOL_TEST(word_part::size()  == 0); 
  SHEOL_TEST(dword_part::size() == 0); 
  SHEOL_TEST(qword_part::size() == 0); 
  
  SHEOL_TEST(byte_part::remaining()  == 0x1000); 
  SHEOL_TEST(word_part::remaining()  == 0x800); 
  SHEOL_TEST(dword_part::remaining() == 0x400); 
  SHEOL_TEST(qword_part::remaining() == 0x200); 

  return sheol::report_errors();
}

