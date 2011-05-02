////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_6AD7A71C_0953_42B4_9DE0_4904CD20178B)
#define SHEOL_6AD7A71C_0953_42B4_9DE0_4904CD20178B

#include <boost/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>

#include <sheol/config.hpp> 
#include <sheol/detect/architecture.hpp>
 
#if !defined(SHEOL_NO_POLYMORPHIC_PROTECTION)
  #include <boost/mpl/not.hpp>
  #include <boost/type_traits/is_polymorphic.hpp>
#endif

#if defined(SHEOL_X86_64_ARCHITECTURE)
  #include <sheol/tagged_ptr.hpp>
#endif

#include <sheol/compile_time_assert.hpp> 

namespace sheol {
namespace memory {

template <typename T, typename Enable = void>
struct pod_variable_size_free_entry;

template <typename T, typename Enable>
struct pod_variable_size_free_entry {
  SHEOL_COMPILE_TIME_ASSERT(
    (boost::mpl::less_equal<
      boost::mpl::size_t<sizeof(void*) * 2>,
      boost::mpl::size_t<sizeof(T)>
    >::value),
    type_is_to_small, (T, boost::mpl::size_t<sizeof(T)>));

  #if !defined(SHEOL_NO_POLYMORPHIC_PROTECTION)
    SHEOL_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T));
  #endif

  // Declare no-ops for expected functionality, so that the only compile-time
  // errors are the static assertions.

  typedef std::size_t size_type;
  
  struct data_type { } data;
  
  enum { object_size = sizeof(T) };
  enum { maximum_array_size = boost::integer_traits<size_type>::const_max };

  void reset (pod_variable_size_free_entry* p = 0, size_type s = 1) { } 
  
  void reset (T* p, size_type s = 1) { } 

  size_type size (void) const
  { return 0; }

  void size (size_type s) { } 

  pod_variable_size_free_entry const* get (void) const
  { return reinterpret_cast<pod_variable_size_free_entry const*>(0); }

  pod_variable_size_free_entry* get (void) 
  { return reinterpret_cast<pod_variable_size_free_entry*>(0); }

  pod_variable_size_free_entry const& operator* (void) const
  { return *get(); }

  pod_variable_size_free_entry& operator* (void)
  { return *get(); }

  pod_variable_size_free_entry const* operator-> (void) const
  { return get(); }

  pod_variable_size_free_entry* operator-> (void) 
  { return get(); }
    
  T const* retrieve (void) const
  { return reinterpret_cast<T const*>(get()); }
  
  T* retrieve (void) 
  { return reinterpret_cast<T*>(get()); }

  bool operator== (pod_variable_size_free_entry const& rhs) const
  { return (get() == rhs.get()) && (size() == rhs.size()); }

  bool operator!= (pod_variable_size_free_entry const& rhs) const
  { return !operator==(rhs); } 
    
  operator bool (void) const
  { return get() != 0; }
};

template <typename T>
struct pod_variable_size_free_entry<T, typename boost::enable_if<
  boost::mpl::less_equal<
    boost::mpl::size_t<sizeof(void*) * 2>,
    boost::mpl::size_t<sizeof(T)>
  >
>::type> {
  #if !defined(SHEOL_NO_POLYMORPHIC_PROTECTION)
    SHEOL_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T));
  #endif

  typedef std::size_t size_type;

  struct data_type {
    pod_variable_size_free_entry* ptr;
    size_type size;
  } data;
  
  enum { object_size = sizeof(T) };
  enum { maximum_array_size = boost::integer_traits<size_type>::const_max };

  void reset (pod_variable_size_free_entry* p = 0, size_type s = 1) {
    data.ptr = p; 
    data.size = s;
  } 
  
  void reset (T* p, size_type s = 1) {
    data.ptr = reinterpret_cast<pod_variable_size_free_entry*>(p);
    data.size = s;
  } 

  size_type size (void) const
  { return data.size; }

  void size (size_type s)
  { data.size = s; }

  pod_variable_size_free_entry const* get (void) const
  { return const_cast<pod_variable_size_free_entry const*>(data.ptr); }

  pod_variable_size_free_entry* get (void) 
  { return data.ptr; }

  pod_variable_size_free_entry const& operator* (void) const
  { return *get(); }

  pod_variable_size_free_entry& operator* (void)
  { return *get(); }

  pod_variable_size_free_entry const* operator-> (void) const
  { return get(); }

  pod_variable_size_free_entry* operator-> (void) 
  { return get(); }
    
  T const* retrieve (void) const
  { return reinterpret_cast<T const*>(get()); }
  
  T* retrieve (void) 
  { return reinterpret_cast<T*>(get()); }

  bool operator== (pod_variable_size_free_entry const& rhs) const
  { return (get() == rhs.get()) && (size() == rhs.size()); }

  bool operator!= (pod_variable_size_free_entry const& rhs) const
  { return !operator==(rhs); } 
    
  operator bool (void) const
  { return get() != 0; }
};

#if defined(SHEOL_X86_64_ARCHITECTURE)
  template <typename T>
  struct pod_variable_size_free_entry<T, typename boost::enable_if<
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
    #if !defined(SHEOL_NO_POLYMORPHIC_PROTECTION)
      SHEOL_COMPILE_TIME_ASSERT(
        boost::mpl::not_<boost::is_polymorphic<T> >::value,
        type_is_polymorphic, (T, boost::mpl::size_t<sizeof(T)>));
    #endif

    typedef sheol::tagged_ptr<pod_variable_size_free_entry> data_type;

    data_type data;

    // This is only a word.
    typedef typename data_type::tag_type size_type;
    
    enum { object_size = sizeof(T) };
    enum { maximum_array_size = boost::integer_traits<size_type>::const_max };

    void reset (pod_variable_size_free_entry* p = 0, size_type s = 1) {
      data.set_ptr(p);
      size(s);
    } 

    void reset (T* p, size_type s = 1) {
      data.set_ptr(reinterpret_cast<pod_variable_size_free_entry*>(p));
      size(s);
    } 
  
    size_type size (void) const
    { return data.get_tag(); }
  
    void size (size_type s)
    { data.set_tag(s); }
  
    pod_variable_size_free_entry const* get (void) const
    { return const_cast<pod_variable_size_free_entry const*>(data.get_ptr()); }
  
    pod_variable_size_free_entry* get (void) 
    { return data.get_ptr(); }
  
    pod_variable_size_free_entry const& operator* (void) const
    { return *get(); }
  
    pod_variable_size_free_entry& operator* (void)
    { return *get(); }
  
    pod_variable_size_free_entry const* operator-> (void) const
    { return get(); } 
  
    pod_variable_size_free_entry* operator-> (void) 
    { return get(); } 
    
    T const* retrieve (void) const
    { return reinterpret_cast<T const*>(get()); }
  
    T* retrieve (void) 
    { return reinterpret_cast<T*>(get()); }
  
    bool operator== (pod_variable_size_free_entry const& rhs) const
    { return (get() == rhs.get()) && (size() == rhs.size()); }
  
    bool operator!= (pod_variable_size_free_entry const& rhs) const
    { return !operator==(rhs); }
      
    operator bool (void) const
    { return data; }
  };
#endif

} // memory
} // sheol

#endif // SHEOL_6AD7A71C_0953_42B4_9DE0_4904CD20178B

