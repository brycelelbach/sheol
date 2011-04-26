////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2008-2009 Tim Blechmann, based on code by Cory Nelson
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(EDK_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599)
#define EDK_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599

#include <boost/detect/architecture.hpp>

#if defined(BOOST_DETECT_X86_64_ARCHITECTURE)
  #include <edk/config.hpp>

  #include <stddef.h>

  #include <boost/config.hpp>
  #include <boost/cstdint.hpp>

  namespace edk {

  template <typename T>
  struct tagged_ptr {
    typedef T value_type;
    typedef boost::uint64_t compressed_ptr_type;
    typedef boost::uint16_t tag_type;

    union cast_unit {
      compressed_ptr_type value;
      tag_type tag[4];
    };

    BOOST_STATIC_CONSTANT(std::size_t, tag_index = 3);
    BOOST_STATIC_CONSTANT(compressed_ptr_type, ptr_mask = 0xffffffffffff);

    static T* extract_ptr (volatile compressed_ptr_type const& i)
    { return reinterpret_cast<T*>(i & ptr_mask); }

    static tag_type extract_tag (volatile compressed_ptr_type const& i) {
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

   public:
    tagged_ptr (void): ptr(0) {}

    tagged_ptr (tagged_ptr const& p): ptr(p.ptr) {}

    explicit tagged_ptr (T* p): ptr(pack_ptr(p, 0)) {}

    tagged_ptr (T* p, tag_type t): ptr(pack_ptr(p, t)) {}

    tagged_ptr& operator= (tagged_ptr const& p) {
      ptr = p.ptr;
      return *this;
    }

    void reset (T* p, tag_type t)
    { ptr = pack_ptr(p, t); }

    bool operator== (volatile tagged_ptr const& p) const
    { return (ptr == p.ptr); }

    bool operator!= (volatile tagged_ptr const& p) const
    { return !operator==(p); }

    T* get_ptr (void) const volatile
    { return extract_ptr(ptr); }

    void set_ptr (T* p) volatile {
      tag_type tag = get_tag();
      ptr = pack_ptr(p, tag);
    }

    tag_type get_tag (void) const volatile
    { return extract_tag(ptr); }

    void set_tag (tag_type t) volatile {
      T * p = get_ptr();
      ptr = pack_ptr(p, t);
    }

    T& operator* (void) const
    { return *get_ptr(); }

    T* operator-> (void) const
    { return get_ptr(); }

    operator bool (void) const
    { return get_ptr() != 0; }

   private:
    compressed_ptr_type ptr;
  };

  } // edk 
#else
    #error Unsupported platform
#endif

#endif // EDK_DEEA4A9D_C2E8_4EB4_8C6C_CC7A5CDA5599

