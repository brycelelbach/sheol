////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008-2009 Tim Blechmann, based on code by Cory Nelson
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_2A6E62CF_42E2_436C_83F4_18A06B3FAA1D)
#define SHEOL_2A6E62CF_42E2_436C_83F4_18A06B3FAA1D

#include <sheol/detect/architecture.hpp>

#if defined(SHEOL_X86_64_ARCHITECTURE)
  #include <sheol/adt/pod_tagged_ptr.hpp>

  namespace sheol {
  namespace adt {

  template <typename T>
  struct tagged_ptr: pod_tagged_ptr<T> {
    typedef pod_tagged_ptr<T> base_type;

   private:
    // Adjust access to the data.
    using base_type::ptr;

   public:
    tagged_ptr (void) {
      base_type::reset();
    }

    tagged_ptr (tagged_ptr& other) {
      base_type::reset(other.get_ptr(), other.get_tag());
    }

    tagged_ptr (T* p, typename base_type::tag_type t = 0) {
      base_type::reset(p, t);
    }

    tagged_ptr& operator= (tagged_ptr& other) {
      base_type::reset(other.get_ptr(), other.get_tag());
      return *this;
    }
    
    tagged_ptr& operator= (T* p) {
      base_type::reset(p);
      return *this;
    }
  };

  } // adt
  } // sheol 
#else
  #error Unsupported platform
#endif

#endif // SHEOL_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599

