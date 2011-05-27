////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_1B7E1CA9_F275_4CE6_895C_27E04D1D8D4C)
#define SHEOL_1B7E1CA9_F275_4CE6_895C_27E04D1D8D4C

#include <sheol/config.hpp>

#include <boost/assert.hpp>
#include <boost/mpl/equal_to.hpp>

#include <sheol/memory/pod_one_size_free_entry.hpp> 
#include <sheol/storage.hpp>

namespace sheol {
namespace memory {

template <std::size_t ObjectSize /* bytes */>
struct pod_one_size_freelist {
  typedef sheol::storage<ObjectSize> value_type;

  typedef std::size_t size_type;

  typedef pod_one_size_free_entry<value_type> entry_type; 
 
  enum { object_size = entry_type::object_size }; // in bytes

  entry_type first;
  entry_type last;

  /* O(1) */
  void construct (void) {
    first.reset();
    last.reset();
  }
  
  /* O(free*size) */
  void destroy (void) {
    // IMPLEMENT
  } 

  /* O(1), returns NULL if empty */
  value_type* allocate (void) {
    if (empty())
      return 0;

    entry_type second = first.get();
  
    // one element in the freelist
    if (!second) {
      BOOST_ASSERT(first.get() == last.get());

      first.reset();
      last.reset();
      
      return second.retrieve();
    }

    first.reset(second.get());
    return second.retrieve();
  }

  /* O(1), returns NULL if empty */
  template <typename T>
  T* allocate (void) {
    SHEOL_COMPILE_TIME_ASSERT(
      (boost::mpl::equal_to<
        boost::mpl::size_t<object_size>,
        boost::mpl::size_t<sizeof(T)>
      >::value),
    type_size_mismatch, (T, boost::mpl::size_t<sizeof(T)>));

    return reinterpret_cast<T*>(allocate());
  }

  /* O(1) */
  bool empty (void) const {
    BOOST_ASSERT((first && last) || (!first && !last));
    return !first && !last;
  }

  /* O(allocate*n) */
  void reserve (size_type objects) {
    // IMPLEMENT
//    for (size_type i = 0; i < objects; ++i) {
//      entry_type* p = reinterpret_cast<entry_type*>(f(object_size));
//      deallocate(p);
//    }
  }

  /* O(1) */
  template <typename T>
  void deallocate (T* p) {
    SHEOL_COMPILE_TIME_ASSERT(
      (boost::mpl::equal_to<
        boost::mpl::size_t<object_size>,
        boost::mpl::size_t<sizeof(T)>
      >::value),
    type_size_mismatch, (T, boost::mpl::size_t<sizeof(T)>));

    if (empty())
      last.reset(reinterpret_cast<entry_type*>(p));

    entry_type& next = *last;

    // the entry last points to should always empty 
    BOOST_ASSERT(!next);

    next.reset(reinterpret_cast<entry_type*>(p));
    last.reset(next.get());
  }
};

} // memory
} // sheol

#endif // SHEOL_1B7E1CA9_F275_4CE6_895C_27E04D1D8D4C

