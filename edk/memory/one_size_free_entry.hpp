////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_6D54A860_A56A_484B_AF0E_1DCFB3BB1EA4)
#define EDK_6D54A860_A56A_484B_AF0E_1DCFB3BB1EA4

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>

#include <edk/config.hpp> 
 
#if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
  #include <boost/type_traits/is_polymorphic.hpp>
#endif

#include <edk/compile_time_assert.hpp> 

namespace edk {
namespace memory {

template <typename T, typename Enable = void>
struct one_size_free_entry;

template <typename T, typename Enable>
struct one_size_free_entry {
  EDK_COMPILE_TIME_ASSERT(
    (boost::mpl::less<
      boost::mpl::size_t<sizeof(void*)>,
      boost::mpl::size_t<sizeof(T)>
    >::value),
    type_is_to_small, (T, boost::mpl::size_t<sizeof(T)>));
  
  #if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
    EDK_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T));
  #endif

  typedef std::size_t size_type;

  enum { object_size = sizeof(T) };
    
 private:
  one_size_free_entry* ptr_;

 public:
  one_size_free_entry (void): ptr_(0) { }
  
  explicit one_size_free_entry (one_size_free_entry* p) {
    reset(p);
  }

  explicit one_size_free_entry (void* p) {
    reset(p);
  }
  
  explicit one_size_free_entry (T* p) {
    reset(p);
  }
  
  one_size_free_entry (one_size_free_entry const& other): ptr_(other.ptr_) { } 
  
  one_size_free_entry& operator= (one_size_free_entry const& other) {
    ptr_ = other.ptr_;
    return *this;
  }
  
  one_size_free_entry& operator= (one_size_free_entry* p) {
    reset(p);
    return *this;
  }
  
  one_size_free_entry& operator= (void* p) {
    reset(p);
    return *this;
  }

  one_size_free_entry& operator= (T* p) {
    reset(p);
    return *this;
  }

  void reset (one_size_free_entry* p = 0) {
    ptr_ = p; 
  }
  
  void reset (void* p) {
    ptr_ = reinterpret_cast<one_size_free_entry*>(p);
  }

  void reset (T* p) {
    ptr_ = reinterpret_cast<one_size_free_entry*>(p);
  } 

  one_size_free_entry const& operator* (void) const
  { return *ptr_; }

  one_size_free_entry& operator* (void)
  { return *ptr_; }

  one_size_free_entry const* operator-> (void) const
  { return ptr_; }

  one_size_free_entry* operator-> (void) 
  { return ptr_; }

  one_size_free_entry const* get (void) const
  { return ptr_; }

  one_size_free_entry* get (void) 
  { return ptr_; }
  
  T const* retrieve (void) const
  { return reinterpret_cast<T const*>(get()); }
  
  T* retrieve (void) 
  { return reinterpret_cast<T*>(get()); }

  bool operator== (one_size_free_entry const& rhs) const
  { return (ptr_ == rhs.ptr_); }

  bool operator!= (one_size_free_entry const& rhs) const
  { return !(*this == rhs); } 
    
  operator bool (void) const
  { return ptr_ != 0; }
};

} // memory
} // edk

#endif // EDK_6D54A860_A56A_484B_AF0E_1DCFB3BB1EA4

