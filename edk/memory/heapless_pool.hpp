////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Joel Falcou 
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_0701C127_B570_4CDC_8DC0_226B8A2E4035)
#define EDK_0701C127_B570_4CDC_8DC0_226B8A2E4035

#include <limits.h>

#include <boost/cstdint.hpp>
#include <boost/integer.hpp>
#include <boost/config.hpp>

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/modulus.hpp>

#include <edk/compile_time_assert.hpp>
#include <edk/config.hpp>

namespace edk {
namespace memory {

template<std::size_t ObjectSize,
         std::size_t Capacity = (1 << 8) * EDK_PAGE_SIZE * ObjectSize,
         std::size_t ID = ObjectSize>
struct heapless_pool {
  EDK_COMPILE_TIME_ASSERT(
    (boost::mpl::less<
      boost::mpl::size_t<ObjectSize>,
      boost::mpl::size_t<Capacity>
    >::value),
    object_size_is_larger_than_capacity,
    (boost::mpl::size_t<ObjectSize>, boost::mpl::size_t<Capacity>));
  
  EDK_COMPILE_TIME_ASSERT(
    (boost::mpl::equal_to<
      boost::mpl::modulus<
        boost::mpl::size_t<Capacity>,
        boost::mpl::size_t<ObjectSize>
      >,
      boost::mpl::size_t<0>
    >::value),
    capacity_must_be_cleanly_divisible_by_object_size,
    (boost::mpl::size_t<ObjectSize>, boost::mpl::size_t<Capacity>));

  typedef boost::uint8_t byte_type;
  typedef boost::uint_t<sizeof(void*) * CHAR_BIT>::exact size_type;

  // Error codes that malloc might return.
  enum { invalid_count = -1 };
  enum { out_of_memory = 0 };

  // Object size of this pool, in bytes.
  enum { object_size = ObjectSize };

  // Capacity of this pool, in bytes.
  enum { capacity = Capacity };

  // Maximum number of objects that this pool can allocate.
  enum { pool_size = Capacity / ObjectSize };

  // Allocates 'count' objects. Returns 'invalid_count' if count is zero, and
  // returns 'out_of_memory' if the pool is exhausted.
  static void* allocate (size_type count = 1) {
    if (EDK_UNLIKELY(count == 0))
      return reinterpret_cast<void*>(invalid_count);
 
    byte_type* new_next = next + (count * ObjectSize);
 
    if (EDK_UNLIKELY(new_next > end))
      return reinterpret_cast<void*>(out_of_memory); 
 
    void* mem = reinterpret_cast<void*>(next);
    next = new_next; 
    return mem; 
  }

  // Returns the number of objects that this pool has allocated.
  static size_type size (void) {
    return static_cast<size_type>((next - buffer) / ObjectSize);
  }

  // Returns the number of objects that this pool can allocate. 
  static size_type remaining (void) {
    return static_cast<size_type>((end - next) / ObjectSize);
  }

  template <typename T>
  static bool owns (T* ptr) {
    size_type const point = reinterpret_cast<size_type const>(ptr);
    size_type const lower = reinterpret_cast<size_type const>(first);
    size_type const upper = reinterpret_cast<size_type const>(end);
    return ((point < upper) && (point >= lower));
  }

  template <typename T>
  static bool owns (T const* ptr) {
    size_type const point = reinterpret_cast<size_type const>(ptr);
    size_type const lower = reinterpret_cast<size_type const>(first);
    size_type const upper = reinterpret_cast<size_type const>(end);
    return ((point < upper) && (point >= lower));
  }

  // We don't want the buffer to go into the .bss section. It would be
  // initialized to zero at runtime by the loader, and expensive serial
  // operations are bad.
  static byte_type buffer[Capacity];
  static byte_type* const first;
  static byte_type* const end;
  static byte_type* next;
};

template<std::size_t ObjectSize, std::size_t Capacity, std::size_t ID>
typename heapless_pool<ObjectSize, Capacity, ID>::byte_type
heapless_pool<ObjectSize, Capacity, ID>::buffer[Capacity];

template<std::size_t ObjectSize, std::size_t Capacity, std::size_t ID>
typename heapless_pool<ObjectSize, Capacity, ID>::byte_type* const
heapless_pool<ObjectSize, Capacity, ID>::first 
  = &heapless_pool<ObjectSize, Capacity, ID>::buffer[0];

template<std::size_t ObjectSize, std::size_t Capacity, std::size_t ID>
typename heapless_pool<ObjectSize, Capacity, ID>::byte_type* const
heapless_pool<ObjectSize, Capacity, ID>::end 
  = &heapless_pool<ObjectSize, Capacity, ID>::buffer[Capacity];

template<std::size_t ObjectSize, std::size_t Capacity, std::size_t ID>
typename heapless_pool<ObjectSize, Capacity, ID>::byte_type*
heapless_pool<ObjectSize, Capacity, ID>::next 
  = heapless_pool<ObjectSize, Capacity, ID>::first;

} // memory
} // edk

#endif // EDK_0701C127_B570_4CDC_8DC0_226B8A2E4035

