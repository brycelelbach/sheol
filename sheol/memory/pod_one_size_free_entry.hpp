////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_6D54A860_A56A_484B_AF0E_1DCFB3BB1EA4)
#define SHEOL_6D54A860_A56A_484B_AF0E_1DCFB3BB1EA4

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>

#include <sheol/config.hpp> 
 
#if !defined(SHEOL_NO_POLYMORPHIC_PROTECTION)
  #include <boost/mpl/not.hpp>
  #include <boost/type_traits/is_polymorphic.hpp>
#endif

#include <sheol/compile_time_assert.hpp> 

namespace sheol {
namespace memory {

template <typename T, typename Enable = void>
struct pod_one_size_free_entry;

template <typename T, typename Enable>
struct pod_one_size_free_entry {
  SHEOL_COMPILE_TIME_ASSERT(
    (boost::mpl::less_equal<
      boost::mpl::size_t<sizeof(void*)>,
      boost::mpl::size_t<sizeof(T)>
    >::value),
    type_is_to_small, (T, boost::mpl::size_t<sizeof(T)>));
  
  #if !defined(SHEOL_NO_POLYMORPHIC_PROTECTION)
    SHEOL_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T));
  #endif

  enum { object_size = sizeof(T) };
  
  typedef pod_one_size_free_entry* data_type;  
  data_type data;

  void reset (pod_one_size_free_entry* p = 0) {
    data = p; 
  }

  void reset (T* p) {
    data = reinterpret_cast<pod_one_size_free_entry*>(p);
  } 

  pod_one_size_free_entry const* get (void) const
  { return const_cast<pod_one_size_free_entry const*>(data); }

  pod_one_size_free_entry* get (void) 
  { return data; }

  pod_one_size_free_entry const& operator* (void) const
  { return *get(); }

  pod_one_size_free_entry& operator* (void)
  { return *get(); }

  pod_one_size_free_entry const* operator-> (void) const
  { return get(); } 

  pod_one_size_free_entry* operator-> (void) 
  { return get(); }
  
  T const* retrieve (void) const
  { return reinterpret_cast<T const*>(get()); }
  
  T* retrieve (void) 
  { return reinterpret_cast<T*>(get()); }

  bool operator== (pod_one_size_free_entry const& rhs) const
  { return (get() == rhs.get()); }

  bool operator!= (pod_one_size_free_entry const& rhs) const
  { return (get() != rhs.get()); } 
    
  operator bool (void) const
  { return get() != 0; }
};

} // memory
} // sheol

#endif // SHEOL_6D54A860_A56A_484B_AF0E_1DCFB3BB1EA4

