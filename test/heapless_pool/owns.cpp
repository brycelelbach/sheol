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
  typedef heapless_pool<1, 0x1000> byte_pool; 
  typedef heapless_pool<2, 0x1000> word_pool;  
  typedef heapless_pool<4, 0x1000> dword_pool; 
  typedef heapless_pool<8, 0x1000> qword_pool; 

  void* first_byte   = byte_pool::allocate(),
      * middle_bytes = byte_pool::allocate(byte_pool::pool_size - 2),
      * last_byte    = byte_pool::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_byte);
  SHEOL_TEST(middle_bytes);
  SHEOL_TEST(last_byte);
  
  void* first_word   = word_pool::allocate(),
      * middle_words = word_pool::allocate(word_pool::pool_size - 2),
      * last_word    = word_pool::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_word);
  SHEOL_TEST(middle_words);
  SHEOL_TEST(last_word);
  
  void* first_dword   = dword_pool::allocate(),
      * middle_dwords = dword_pool::allocate(dword_pool::pool_size - 2),
      * last_dword    = dword_pool::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_dword);
  SHEOL_TEST(middle_dwords);
  SHEOL_TEST(last_dword);

  void* first_qword   = qword_pool::allocate(),
      * middle_qwords = qword_pool::allocate(qword_pool::pool_size - 2),
      * last_qword    = qword_pool::allocate();

  // Make sure all allocations were successful.
  SHEOL_TEST(first_qword);
  SHEOL_TEST(middle_qwords);
  SHEOL_TEST(last_qword);

  SHEOL_TEST(byte_pool::owns(first_byte));
  SHEOL_TEST(byte_pool::owns(middle_bytes));
  SHEOL_TEST(byte_pool::owns(last_byte));
  SHEOL_TEST(!byte_pool::owns(first_word));
  SHEOL_TEST(!byte_pool::owns(middle_words));
  SHEOL_TEST(!byte_pool::owns(last_word));
  SHEOL_TEST(!byte_pool::owns(first_dword));
  SHEOL_TEST(!byte_pool::owns(middle_dwords));
  SHEOL_TEST(!byte_pool::owns(last_dword));
  SHEOL_TEST(!byte_pool::owns(first_qword));
  SHEOL_TEST(!byte_pool::owns(middle_qwords));
  SHEOL_TEST(!byte_pool::owns(last_qword));
  
  SHEOL_TEST(!word_pool::owns(first_byte));
  SHEOL_TEST(!word_pool::owns(middle_bytes));
  SHEOL_TEST(!word_pool::owns(last_byte));
  SHEOL_TEST(word_pool::owns(first_word));
  SHEOL_TEST(word_pool::owns(middle_words));
  SHEOL_TEST(word_pool::owns(last_word));
  SHEOL_TEST(!word_pool::owns(first_dword));
  SHEOL_TEST(!word_pool::owns(middle_dwords));
  SHEOL_TEST(!word_pool::owns(last_dword));
  SHEOL_TEST(!word_pool::owns(first_qword));
  SHEOL_TEST(!word_pool::owns(middle_qwords));
  SHEOL_TEST(!word_pool::owns(last_qword));
  
  SHEOL_TEST(!dword_pool::owns(first_byte));
  SHEOL_TEST(!dword_pool::owns(middle_bytes));
  SHEOL_TEST(!dword_pool::owns(last_byte));
  SHEOL_TEST(!dword_pool::owns(first_word));
  SHEOL_TEST(!dword_pool::owns(middle_words));
  SHEOL_TEST(!dword_pool::owns(last_word));
  SHEOL_TEST(dword_pool::owns(first_dword));
  SHEOL_TEST(dword_pool::owns(middle_dwords));
  SHEOL_TEST(dword_pool::owns(last_dword));
  SHEOL_TEST(!dword_pool::owns(first_qword));
  SHEOL_TEST(!dword_pool::owns(middle_qwords));
  SHEOL_TEST(!dword_pool::owns(last_qword));
  
  SHEOL_TEST(!qword_pool::owns(first_byte));
  SHEOL_TEST(!qword_pool::owns(middle_bytes));
  SHEOL_TEST(!qword_pool::owns(last_byte));
  SHEOL_TEST(!qword_pool::owns(first_word));
  SHEOL_TEST(!qword_pool::owns(middle_words));
  SHEOL_TEST(!qword_pool::owns(last_word));
  SHEOL_TEST(!qword_pool::owns(first_dword));
  SHEOL_TEST(!qword_pool::owns(middle_dwords));
  SHEOL_TEST(!qword_pool::owns(last_dword));
  SHEOL_TEST(qword_pool::owns(first_qword));
  SHEOL_TEST(qword_pool::owns(middle_qwords));
  SHEOL_TEST(qword_pool::owns(last_qword));

  return sheol::report_errors();
}

