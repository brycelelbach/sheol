////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008-2009 Tim Blechmann, based on code by Cory Nelson
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599)
#define SHEOL_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599

#include <sheol/detect/architecture.hpp>

#if defined(SHEOL_X86_64_ARCHITECTURE)
  #include <sheol/config.hpp>

  #include <stddef.h>

  #include <boost/config.hpp>
  #include <boost/cstdint.hpp>

  namespace sheol {
  namespace adt {

  template <typename T>
  struct pod_tagged_ptr {
    typedef T value_type;
    typedef boost::uint64_t compressed_ptr_type;
    typedef boost::uint16_t tag_type;

    union cast_unit {
      compressed_ptr_type value;
      tag_type tag[4];
    };

    enum { tag_index = 3 };
    enum { ptr_mask = 0xffffffffffff };

    static T* extract_ptr (compressed_ptr_type volatile const& i)
    { return reinterpret_cast<T*>(i & ptr_mask); }

    static tag_type extract_tag (compressed_ptr_type volatile const& i) {
      cast_unit cu;
      cu.value = i;
      return cu.tag[tag_index];
    }

    static compressed_ptr_type pack_ptr (T* ptr, tag_type tag) {
      cast_unit ret;
      ret.value = reinterpret_cast<compressed_ptr_type>(ptr);
      ret.tag[tag_index] = tag;
      return ret.value;
    }

    void reset (T* p = 0, tag_type t = 0) volatile
    { ptr = pack_ptr(p, t); }

    T const* get_ptr (void) const volatile
    { return extract_ptr(ptr); }

    T* get_ptr (void) volatile
    { return extract_ptr(ptr); }

    void set_ptr (T* p) volatile {
      tag_type tag = get_tag();
      ptr = pack_ptr(p, tag);
    }

    tag_type get_tag (void) const volatile
    { return extract_tag(ptr); }

    void set_tag (tag_type t) volatile {
      T* p = get_ptr();
      ptr = pack_ptr(p, t);
    }

    T const& operator* (void) const volatile
    { return *get_ptr(); }

    T& operator* (void) volatile
    { return *get_ptr(); }

    T const* operator-> (void) const volatile
    { return get_ptr(); }

    T* operator-> (void) volatile
    { return get_ptr(); }

    operator bool (void) const volatile
    { return get_ptr() != 0; }
    
    bool operator== (pod_tagged_ptr volatile const& rhs) const volatile
    { return (get_ptr() == rhs.get_ptr()) && (get_tag() == rhs.get_tag()); }

    bool operator!= (pod_tagged_ptr volatile const& rhs) const volatile
    { return !operator==(rhs); }

    compressed_ptr_type ptr;
  };

  } // adt
  } // sheol 
#else
  #error Unsupported platform
#endif

#endif // SHEOL_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599

