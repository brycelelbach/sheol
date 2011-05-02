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
#include <boost/mpl/and.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>

#include <edk/config.hpp> 
 
#if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
  #include <boost/mpl/not.hpp>
  #include <boost/type_traits/is_polymorphic.hpp>
#endif

#if defined(BOOST_DETECT_X86_64_ARCHITECTURE)
  #include <edk/tagged_ptr.hpp>
#endif

#include <edk/compile_time_assert.hpp> 

namespace edk {
namespace memory {

template <typename T, typename Enable = void>
struct variable_size_free_entry;

template <typename T, typename Enable>
struct variable_size_free_entry {
  EDK_COMPILE_TIME_ASSERT(
    (boost::mpl::less_equal<
      boost::mpl::size_t<sizeof(void*) * 2>,
      boost::mpl::size_t<sizeof(T)>
    >::value),
    type_is_to_small, (T, boost::mpl::size_t<sizeof(T)>));
};

template <typename T>
struct variable_size_free_entry<T, typename boost::enable_if<
  boost::mpl::less_equal<
    boost::mpl::size_t<sizeof(void*) * 2>,
    boost::mpl::size_t<sizeof(T)>
  >
>::type> {
  #if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
    EDK_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T));
  #endif

  typedef std::size_t size_type;

  enum { object_size = sizeof(T) };

  enum { maximum_array_size = boost::integer_traits<size_type>::const_max };

 private:
  variable_size_free_entry* ptr_;
  size_type size_;

 public:
  variable_size_free_entry (void): ptr_(0), size_(1) { }
  
  explicit variable_size_free_entry (variable_size_free_entry* p,
                                     size_type s = 1)
  {
    reset(p, s);
  }
  
  explicit variable_size_free_entry (void* p, size_type s = 1) {
    reset(p, s);
  }

  explicit variable_size_free_entry (T* p, size_type s = 1) {
    reset(p, s);
  }
  
  variable_size_free_entry (variable_size_free_entry const& other):
    ptr_(other.ptr_), size_(other.size_) { } 
  
  variable_size_free_entry& operator= (variable_size_free_entry const& other) {
    ptr_ = other.ptr_;
    size_ = other.size_;
    return *this;
  }
  
  variable_size_free_entry& operator= (variable_size_free_entry* p) {
    reset(p);
    return *this;
  }
  
  variable_size_free_entry& operator= (void* p) {
    reset(p);
    return *this;
  }

  variable_size_free_entry& operator= (T* p) {
    reset(p);
    return *this;
  }
  
  void reset (variable_size_free_entry* p = 0, size_type s = 1) {
    ptr_ = p; 
    size_ = s;
  } 
  
  void reset (void* p, size_type s = 1) {
    ptr_ = reinterpret_cast<variable_size_free_entry*>(p);
    size_ = s;
  } 

  void reset (T* p, size_type s = 1) {
    ptr_ = reinterpret_cast<variable_size_free_entry*>(p);
    size_ = s;
  } 

  size_type size (void) const
  { return size_; }

  void size (size_type s)
  { size_ = s; }

  variable_size_free_entry const& operator* (void) const
  { return *ptr_; }

  variable_size_free_entry& operator* (void)
  { return *ptr_; }

  variable_size_free_entry const* operator-> (void) const
  { return ptr_; }

  variable_size_free_entry* operator-> (void) 
  { return ptr_; }

  variable_size_free_entry const* get (void) const
  { return ptr_; }

  variable_size_free_entry* get (void) 
  { return ptr_; }
    
  T const* retrieve (void) const
  { return reinterpret_cast<T const*>(get()); }
  
  T* retrieve (void) 
  { return reinterpret_cast<T*>(get()); }

  bool operator== (variable_size_free_entry const& rhs) const
  { return (ptr_ == rhs.ptr_) && (size_ == rhs.size_); }

  bool operator!= (variable_size_free_entry const& rhs) const
  { return !(*this == rhs); } 
    
  operator bool (void) const
  { return ptr_ != 0; }
};

#if defined(BOOST_DETECT_X86_64_ARCHITECTURE)
  template <typename T>
  struct variable_size_free_entry<T, typename boost::enable_if<
    boost::mpl::and_<
      boost::mpl::less_equal<
        boost::mpl::size_t<sizeof(void*)>,
        boost::mpl::size_t<sizeof(T)>
      >,
      boost::mpl::less<
        boost::mpl::size_t<sizeof(T)>,
        boost::mpl::size_t<sizeof(void*) * 2>
      >
    > 
  >::type> {
    #if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
      EDK_COMPILE_TIME_ASSERT(
        boost::mpl::not_<boost::is_polymorphic<T> >::value,
        type_is_polymorphic, (T, boost::mpl::size_t<sizeof(T)>));
    #endif

    typedef edk::tagged_ptr<variable_size_free_entry> tagged_ptr_type;

    // This is only a word.
    typedef typename tagged_ptr_type::tag_type size_type;

    enum { object_size = sizeof(T) };

    enum { maximum_array_size = boost::integer_traits<size_type>::const_max };

   private:
    tagged_ptr_type ptr_;
  
   public:
    variable_size_free_entry (void) {
      reset(reinterpret_cast<void*>(0), 1);
    }
    
    explicit variable_size_free_entry (variable_size_free_entry* p,
                                       size_type s = 1)
    {
      reset(p, s);
    }
    
    explicit variable_size_free_entry (void* p, size_type s = 1) {
      reset(p, s);
    }
  
    explicit variable_size_free_entry (T* p, size_type s = 1) {
      reset(p, s);
    }
    
    variable_size_free_entry (variable_size_free_entry const& other):
      ptr_(other.ptr_) { } 
    
    variable_size_free_entry& operator= (variable_size_free_entry const& other) {
      ptr_ = other.ptr_; 
      return *this;
    }
    
    variable_size_free_entry& operator= (variable_size_free_entry* p) {
      reset(p);
      return *this;
    }
    
    variable_size_free_entry& operator= (void* p) {
      reset(p);
      return *this;
    }
  
    variable_size_free_entry& operator= (T* p) {
      reset(p);
      return *this;
    }
  
    void reset (variable_size_free_entry* p = 0, size_type s = 1) {
      ptr_.set_ptr(reinterpret_cast<variable_size_free_entry*>(p));
      size(s);
    } 
  
    void reset (void* p, size_type s = 1) {
      ptr_.set_ptr(reinterpret_cast<variable_size_free_entry*>(p));
      size(s);
    } 

    void reset (T* p, size_type s = 1) {
      ptr_.set_ptr(reinterpret_cast<variable_size_free_entry*>(p));
      size(s);
    } 
  
    size_type size (void) const
    { return ptr_.get_tag(); }
  
    void size (size_type s)
    { ptr_.set_tag(s); }
  
    variable_size_free_entry const& operator* (void) const
    { return *ptr_.get_ptr(); }
  
    variable_size_free_entry& operator* (void)
    { return *ptr_.get_ptr(); }
  
    variable_size_free_entry const* operator-> (void) const
    { return ptr_.get_ptr(); }
  
    variable_size_free_entry* operator-> (void) 
    { return ptr_.get_ptr(); }
  
    variable_size_free_entry const* get (void) const
    { return ptr_.get_ptr(); }
  
    variable_size_free_entry* get (void) 
    { return ptr_.get_ptr(); }
    
    T const* retrieve (void) const
    { return reinterpret_cast<T const*>(get()); }
  
    T* retrieve (void) 
    { return reinterpret_cast<T*>(get()); }
  
    bool operator== (variable_size_free_entry const& rhs) const
    { return (ptr_ == rhs.ptr_); }
  
    bool operator!= (variable_size_free_entry const& rhs) const
    { return !(*this == rhs); } 
      
    operator bool (void) const
    { return ptr_; }
  };
#endif

} // memory
} // edk

#endif // EDK_6AD7A71C_0953_42B4_9DE0_4904CD20178B

