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
  typedef heapless_partition<1, 0x1000> byte_part; 
  typedef heapless_partition<2, 0x1000> word_part;  
  typedef heapless_partition<4, 0x1000> dword_part; 
  typedef heapless_partition<8, 0x1000> qword_part; 

  void* first_byte   = byte_part::allocate(),
      * middle_bytes = byte_part::allocate(byte_part::partition_size - 2),
      * last_byte    = byte_part::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_byte);
  SHEOL_TEST(middle_bytes);
  SHEOL_TEST(last_byte);
  
  void* first_word   = word_part::allocate(),
      * middle_words = word_part::allocate(word_part::partition_size - 2),
      * last_word    = word_part::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_word);
  SHEOL_TEST(middle_words);
  SHEOL_TEST(last_word);
  
  void* first_dword   = dword_part::allocate(),
      * middle_dwords = dword_part::allocate(dword_part::partition_size - 2),
      * last_dword    = dword_part::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_dword);
  SHEOL_TEST(middle_dwords);
  SHEOL_TEST(last_dword);

  void* first_qword   = qword_part::allocate(),
      * middle_qwords = qword_part::allocate(qword_part::partition_size - 2),
      * last_qword    = qword_part::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_qword);
  SHEOL_TEST(middle_qwords);
  SHEOL_TEST(last_qword);

  SHEOL_TEST(byte_part::owns(first_byte));
  SHEOL_TEST(byte_part::owns(middle_bytes));
  SHEOL_TEST(byte_part::owns(last_byte));
  SHEOL_TEST(!byte_part::owns(first_word));
  SHEOL_TEST(!byte_part::owns(middle_words));
  SHEOL_TEST(!byte_part::owns(last_word));
  SHEOL_TEST(!byte_part::owns(first_dword));
  SHEOL_TEST(!byte_part::owns(middle_dwords));
  SHEOL_TEST(!byte_part::owns(last_dword));
  SHEOL_TEST(!byte_part::owns(first_qword));
  SHEOL_TEST(!byte_part::owns(middle_qwords));
  SHEOL_TEST(!byte_part::owns(last_qword));
  
  SHEOL_TEST(!word_part::owns(first_byte));
  SHEOL_TEST(!word_part::owns(middle_bytes));
  SHEOL_TEST(!word_part::owns(last_byte));
  SHEOL_TEST(word_part::owns(first_word));
  SHEOL_TEST(word_part::owns(middle_words));
  SHEOL_TEST(word_part::owns(last_word));
  SHEOL_TEST(!word_part::owns(first_dword));
  SHEOL_TEST(!word_part::owns(middle_dwords));
  SHEOL_TEST(!word_part::owns(last_dword));
  SHEOL_TEST(!word_part::owns(first_qword));
  SHEOL_TEST(!word_part::owns(middle_qwords));
  SHEOL_TEST(!word_part::owns(last_qword));
  
  SHEOL_TEST(!dword_part::owns(first_byte));
  SHEOL_TEST(!dword_part::owns(middle_bytes));
  SHEOL_TEST(!dword_part::owns(last_byte));
  SHEOL_TEST(!dword_part::owns(first_word));
  SHEOL_TEST(!dword_part::owns(middle_words));
  SHEOL_TEST(!dword_part::owns(last_word));
  SHEOL_TEST(dword_part::owns(first_dword));
  SHEOL_TEST(dword_part::owns(middle_dwords));
  SHEOL_TEST(dword_part::owns(last_dword));
  SHEOL_TEST(!dword_part::owns(first_qword));
  SHEOL_TEST(!dword_part::owns(middle_qwords));
  SHEOL_TEST(!dword_part::owns(last_qword));
  
  SHEOL_TEST(!qword_part::owns(first_byte));
  SHEOL_TEST(!qword_part::owns(middle_bytes));
  SHEOL_TEST(!qword_part::owns(last_byte));
  SHEOL_TEST(!qword_part::owns(first_word));
  SHEOL_TEST(!qword_part::owns(middle_words));
  SHEOL_TEST(!qword_part::owns(last_word));
  SHEOL_TEST(!qword_part::owns(first_dword));
  SHEOL_TEST(!qword_part::owns(middle_dwords));
  SHEOL_TEST(!qword_part::owns(last_dword));
  SHEOL_TEST(qword_part::owns(first_qword));
  SHEOL_TEST(qword_part::owns(middle_qwords));
  SHEOL_TEST(qword_part::owns(last_qword));

  return sheol::report_errors();
}

