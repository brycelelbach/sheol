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

  typedef heapless_pool<1, 0x1000> byte_pool; 
  typedef heapless_pool<2, 0x1000> word_pool;  
  typedef heapless_pool<4, 0x1000> dword_pool; 
  typedef heapless_pool<8, 0x1000> qword_pool; 

  void* first_byte   = byte_pool::allocate(),
        middle_bytes = byte_pool::allocate(byte_pool::pool_size - 2),
        last_byte    = byte_pool::allocate();

  // Make sure all allocations were successful.
  BOOST_TEST(first_byte);
  BOOST_TEST(middle_bytes);
  BOOST_TEST(last_byte);
  
  void* first_word   = word_pool::allocate(),
        middle_words = word_pool::allocate(word_pool::pool_size - 2),
        last_word    = word_pool::allocate();

  // Make sure all allocations were successful.
  BOOST_TEST(first_word);
  BOOST_TEST(middle_words);
  BOOST_TEST(last_word);
  
  void* first_dword   = dword_pool::allocate(),
        middle_dwords = dword_pool::allocate(dword_pool::pool_size - 2),
        last_dword    = dword_pool::allocate();

  // Make sure all allocations were successful.
  BOOST_TEST(first_dword);
  BOOST_TEST(middle_dwords);
  BOOST_TEST(last_dword);

  void* first_qword   = qword_pool::allocate(),
        middle_qwords = qword_pool::allocate(qword_pool::pool_size - 2),
        last_qword    = qword_pool::allocate();

  // Make sure all allocations were successful.
  BOOST_TEST(first_qword);
  BOOST_TEST(middle_qwords);
  BOOST_TEST(last_qword);

  BOOST_TEST(byte_pool::owns(first_byte));
  BOOST_TEST(byte_pool::owns(middle_bytes));
  BOOST_TEST(byte_pool::owns(last_byte));
  BOOST_TEST(!byte_pool::owns(first_word));
  BOOST_TEST(!byte_pool::owns(middle_words));
  BOOST_TEST(!byte_pool::owns(last_word));
  BOOST_TEST(!byte_pool::owns(first_dword));
  BOOST_TEST(!byte_pool::owns(middle_dwords));
  BOOST_TEST(!byte_pool::owns(last_dword));
  BOOST_TEST(!byte_pool::owns(first_qword));
  BOOST_TEST(!byte_pool::owns(middle_qwords));
  BOOST_TEST(!byte_pool::owns(last_qword));
  
  BOOST_TEST(!byte_pool::owns(first_byte));
  BOOST_TEST(!byte_pool::owns(middle_bytes));
  BOOST_TEST(!byte_pool::owns(last_byte));
  BOOST_TEST(byte_pool::owns(first_word));
  BOOST_TEST(byte_pool::owns(middle_words));
  BOOST_TEST(byte_pool::owns(last_word));
  BOOST_TEST(!byte_pool::owns(first_dword));
  BOOST_TEST(!byte_pool::owns(middle_dwords));
  BOOST_TEST(!byte_pool::owns(last_dword));
  BOOST_TEST(!byte_pool::owns(first_qword));
  BOOST_TEST(!byte_pool::owns(middle_qwords));
  BOOST_TEST(!byte_pool::owns(last_qword));
  
  BOOST_TEST(!byte_pool::owns(first_byte));
  BOOST_TEST(!byte_pool::owns(middle_bytes));
  BOOST_TEST(!byte_pool::owns(last_byte));
  BOOST_TEST(!byte_pool::owns(first_word));
  BOOST_TEST(!byte_pool::owns(middle_words));
  BOOST_TEST(!byte_pool::owns(last_word));
  BOOST_TEST(byte_pool::owns(first_dword));
  BOOST_TEST(byte_pool::owns(middle_dwords));
  BOOST_TEST(byte_pool::owns(last_dword));
  BOOST_TEST(!byte_pool::owns(first_qword));
  BOOST_TEST(!byte_pool::owns(middle_qwords));
  BOOST_TEST(!byte_pool::owns(last_qword));
  
  BOOST_TEST(!byte_pool::owns(first_byte));
  BOOST_TEST(!byte_pool::owns(middle_bytes));
  BOOST_TEST(!byte_pool::owns(last_byte));
  BOOST_TEST(!byte_pool::owns(first_word));
  BOOST_TEST(!byte_pool::owns(middle_words));
  BOOST_TEST(!byte_pool::owns(last_word));
  BOOST_TEST(!byte_pool::owns(first_dword));
  BOOST_TEST(!byte_pool::owns(middle_dwords));
  BOOST_TEST(!byte_pool::owns(last_dword));
  BOOST_TEST(byte_pool::owns(first_qword));
  BOOST_TEST(byte_pool::owns(middle_qwords));
  BOOST_TEST(byte_pool::owns(last_qword));

  return boost::report_errors();
}

