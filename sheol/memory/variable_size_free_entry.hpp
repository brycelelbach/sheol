////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_D738A76C_82DD_486C_A5BA_977BDC308811)
#define SHEOL_D738A76C_82DD_486C_A5BA_977BDC308811

#include <sheol/memory/pod_variable_size_free_entry.hpp> 

namespace sheol {
namespace memory {

template <typename T, typename Enable = void>
struct variable_size_free_entry;

template <typename T, typename Enable>
struct variable_size_free_entry: pod_variable_size_free_entry<T> {
  typedef pod_variable_size_free_entry<T> base_type;

 private:
  // Adjust access to the data.
  using base_type::data;

 public:
  variable_size_free_entry (void)
  { base_type::reset(); }
  
  variable_size_free_entry (base_type* p, typename base_type::size_type s = 1)
  { base_type::reset(p, s); }
  
  explicit variable_size_free_entry (T* p, typename base_type::size_type s = 1)
  { base_type::reset(p, s); }
  
  variable_size_free_entry (base_type& other)
  { base_type::reset(other.get(), other.size()); } 
  
  variable_size_free_entry& operator= (base_type& other) {
    base_type::reset(other.get(), other.size());
    return *this;
  }
  
  variable_size_free_entry& operator= (base_type* p) {
    base_type::reset(p);
    return *this;
  }

  variable_size_free_entry& operator= (T* p) {
    base_type::reset(p);
    return *this;
  }
};

} // memory
} // sheol

#endif // SHEOL_D738A76C_82DD_486C_A5BA_977BDC308811

