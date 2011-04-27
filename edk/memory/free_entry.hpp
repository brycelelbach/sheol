////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_6AD7A71C_0953_42B4_9DE0_4904CD20178B)
#define EDK_6AD7A71C_0953_42B4_9DE0_4904CD20178B

#include <boost/config.hpp>
#include <boost/detect/architecture.hpp>
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

#if defined(BOOST_DETECT_X86_64_ARCHITECTURE)
  #include <edk/tagged_ptr.hpp>
#endif

#include <edk/compile_time_assert.hpp> 

namespace edk {
namespace memory {

template <typename T, typename Enable = void>
struct free_entry;

template <typename T, typename Enable>
struct free_entry {
  EDK_COMPILE_TIME_ASSERT(
    (boost::mpl::less<
      boost::mpl::size_t<sizeof(void*) * 2>,
      boost::mpl::size_t<sizeof(T)>
    >::value),
    type_is_to_small, (T, boost::mpl::size_t<sizeof(T)>));
  
  #if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
    EDK_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T));
  #endif

  typedef std::size_t size_type;

  BOOST_STATIC_CONSTANT(size_type, object_size = sizeof(T));
    
  BOOST_STATIC_CONSTANT(size_type, maximum_array_size =
    boost::integer_traits<size_type>::const_max);

 private:
  free_entry* ptr_;
  size_type size_;

 public:
  free_entry (void): ptr_(0), size_(0) { }

  template <typename Ptr>
  free_entry (Ptr* p, size_type s = 1) {
    reset(p, s);
  }
  
  free_entry (free_entry const& other): ptr_(other.ptr_), size_(other.size_) { } 
  
  free_entry& operator= (free_entry const& other) {
    ptr_ = other.ptr_;
    size_ = other.size_;
  }

  template <typename Ptr>
  free_entry& operator= (Ptr* p) {
    reset(p);
    return *this;
  }

  template <typename Ptr>
  void reset (Ptr* p = 0, size_type s = 1) {
    ptr_ = reinterpret_cast<free_entry*>(p);
    size_ = s;
  } 

  size_type size (void) const
  { return size_; }

  void size (size_type s)
  { size_ = s; }

  free_entry const& operator* (void) const
  { return *ptr_; }

  free_entry& operator* (void)
  { return *ptr_; }

  free_entry const* operator-> (void) const
  { return ptr_; }

  free_entry* operator-> (void) 
  { return ptr_; }

  free_entry const* get (void) const
  { return ptr_; }

  free_entry* get (void) 
  { return ptr_; }

  bool operator== (free_entry const& rhs) const
  { return (ptr_ == rhs.ptr_) && (size_ == rhs.size_); }

  bool operator!= (free_entry const& rhs) const
  { return !(*this == rhs); } 
    
  operator bool (void) const
  { return ptr_ != 0; }
};

#if defined(BOOST_DETECT_X86_64_ARCHITECTURE)
  template <typename T>
  struct free_entry<T, typename boost::enable_if<
    boost::mpl::equal_to<
      boost::mpl::size_t<sizeof(void*)>,
      boost::mpl::size_t<sizeof(T)>
    >
  >::type> {
    #if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
      EDK_COMPILE_TIME_ASSERT(
        boost::mpl::not_<boost::is_polymorphic<T> >::value,
        type_is_polymorphic, (T, boost::mpl::size_t<sizeof(T)>));
    #endif

    typedef edk::tagged_ptr<free_entry> tagged_ptr_type;

    // This is only a word.
    typedef typename tagged_ptr_type::tag_type size_type;

    BOOST_STATIC_CONSTANT(size_type, object_size = sizeof(T));

    BOOST_STATIC_CONSTANT(size_type, maximum_array_size =
      boost::integer_traits<size_type>::const_max);

   private:
    tagged_ptr_type ptr_;
  
   public:
    free_entry (void): ptr_() { }
  
    template <typename Ptr>
    free_entry (Ptr* p, size_type s = 1) {
      reset(p, s);
    }
    
    free_entry (free_entry const& other): ptr_(other.ptr_) { } 
    
    free_entry& operator= (free_entry const& other) {
      ptr_ = other.ptr_; 
      return *this;
    }
  
    template <typename Ptr>
    free_entry& operator= (Ptr* p) {
      reset(p);
      return *this;
    }
  
    template <typename Ptr>
    void reset (Ptr* p = 0, size_type s = 1) {
      ptr_.set_ptr(reinterpret_cast<free_entry*>(p));
      size(s);
    } 
  
    size_type size (void) const
    { return ptr_.get_tag(); }
  
    void size (size_type s)
    { ptr_.set_tag(s); }
  
    free_entry const& operator* (void) const
    { return *ptr_.get_ptr(); }
  
    free_entry& operator* (void)
    { return *ptr_.get_ptr(); }
  
    free_entry const* operator-> (void) const
    { return ptr_.get_ptr(); }
  
    free_entry* operator-> (void) 
    { return ptr_.get_ptr(); }
  
    free_entry const* get (void) const
    { return ptr_.get_ptr(); }
  
    free_entry* get (void) 
    { return ptr_.get_ptr(); }
  
    bool operator== (free_entry const& rhs) const
    { return (ptr_ == rhs.ptr_); }
  
    bool operator!= (free_entry const& rhs) const
    { return !(*this == rhs); } 
      
    operator bool (void) const
    { return ptr_; }
  };
#endif

} // memory
} // edk

#endif // EDK_6AD7A71C_0953_42B4_9DE0_4904CD20178B

