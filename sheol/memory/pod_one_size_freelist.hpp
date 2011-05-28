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

template <std::size_t ObjectSize /* bytes */,
          typename Alloc = std::allocator<sheol::storage<ObjectSize> > >
struct pod_one_size_freelist {
  typedef sheol::storage<ObjectSize> value_type;

  typedef std::size_t size_type;

  typedef pod_one_size_free_entry<value_type> entry_type; 
  
  typedef Alloc allocator_type;
 
  enum { object_size = entry_type::object_size }; // in bytes

  entry_type first;
  entry_type last;
  size_type size_;

  /* O(1) */
  void construct (void) {
    first.reset();
    last.reset();
    size_ = 0;
  }
 
  /* O(1) */
  size_type size (void) const {
    BOOST_ASSERT((first && last && size_) || (!first && !last && !size_));
    return size_;
  }
 
  /* O(size()) */
  void clear (void) {
    value_type* p(0);
    
    while ((p = get())) 
      allocator_type().deallocate(p, 1);
  } 
  
  /* O(1), returns NULL if allocator_type::allocate() returns NULL. */
  value_type* allocate (void) {
    // try to get a recycled block
    value_type* p(get());

    if (p)
      return p;

    // no recycled blocks available, allocate a new block
    return allocator_type().allocate(1);
  } 
  
  /* O(1), returns NULL if allocator_type::allocate() returns NULL. */
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

  /* O(1), returns NULL if empty. */
  value_type* get (void) {
    if (empty())
      return 0;

    entry_type second = *first;
  
    // one element in the freelist
    if (!second) {
      BOOST_ASSERT(size_ == 1);
      BOOST_ASSERT(first.get() == last.get());

      first.reset();
      last.reset();
      size_ = 0; 
      
      return second.retrieve();
    }

    BOOST_ASSERT(size_ > 1);

    --size_;
    first.reset(second.get());
    return second.retrieve();
  }

  /* O(1), returns NULL if empty. */
  template <typename T>
  T* get (void) {
    SHEOL_COMPILE_TIME_ASSERT(
      (boost::mpl::equal_to<
        boost::mpl::size_t<object_size>,
        boost::mpl::size_t<sizeof(T)>
      >::value),
    type_size_mismatch, (T, boost::mpl::size_t<sizeof(T)>));

    return reinterpret_cast<T*>(get());
  }

  /* O(1) */
  bool empty (void) const {
    BOOST_ASSERT((first.get() && last.get() && size_)
              || (!first.get() && !last.get() && !size_));
    return !first && !last && !size_;
  }

  /* O(abs(objects-size())) */
  void reserve (size_type objects) {
    if (objects == size_)
      return;

    // increase
    if (objects > size_) {
      const size_type request = objects - size_; 
      for (size_type i = 0; i < request; ++i) {
        value_type* p = allocator_type().allocate(1);
        deallocate(p);
      }
    }

    // decrease
    else {
      const size_type request = size_ - objects; 
      for (size_type i = 0; i < request; ++i) {
        value_type* p(get());
        BOOST_ASSERT(p);
        allocator_type().deallocate(p, 1); 
      }
    }
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

    // the entry last points to should always be empty 
    BOOST_ASSERT(!next);

    next.reset(reinterpret_cast<entry_type*>(p));
    last.reset(next.get());
    ++size_;
  }
};

} // memory
} // sheol

#endif // SHEOL_1B7E1CA9_F275_4CE6_895C_27E04D1D8D4C

