////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_651FADDA_14B8_4443_9F84_144460121BAD)
#define SHEOL_651FADDA_14B8_4443_9F84_144460121BAD

#include <sheol/memory/pod_one_size_free_entry.hpp> 

namespace sheol {
namespace memory {

template <typename T, typename Enable = void>
struct one_size_free_entry;

template <typename T, typename Enable>
struct one_size_free_entry: pod_one_size_free_entry<T> {
  typedef pod_one_size_free_entry<T> base_type;

 private:
  // Adjust access to the data.
  using base_type::data;

 public:
  one_size_free_entry (void) {
    base_type::reset();
  }
  
  explicit one_size_free_entry (base_type* p) {
    base_type::reset(p);
  }

  explicit one_size_free_entry (T* p) {
    base_type::reset(p);
  }
  
  one_size_free_entry (one_size_free_entry& other) {
    base_type::reset(other.get());
  } 
  
  one_size_free_entry (base_type& other) {
    base_type::reset(other.get());
  } 
  
  one_size_free_entry& operator= (one_size_free_entry& other) {
    base_type::reset(other.get());
    return *this;
  }
  
  one_size_free_entry& operator= (base_type& other) {
    base_type::reset(other.get());
    return *this;
  }
  
  one_size_free_entry& operator= (base_type* p) {
    base_type::reset(p);
    return *this;
  }

  one_size_free_entry& operator= (T* p) {
    base_type::reset(p);
    return *this;
  }
};

} // memory
} // sheol

#endif // SHEOL_651FADDA_14B8_4443_9F84_144460121BAD

