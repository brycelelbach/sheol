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
    boost::less<
      boost::mpl::size_t<sizeof(void*)>,
      boost::mpl::size_t<sizeof(T)>
    >::value,
    type_is_to_small, (T, boost::mpl::size_t<sizeof(T)>));
  
  #if !defined(EDK_NO_POLYMORPHIC_PROTECTION)
    EDK_COMPILE_TIME_ASSERT(
      boost::mpl::not_<boost::is_polymorphic<T> >::value,
      type_is_polymorphic, (T, boost::mpl::size_t<sizeof(T)>));
  #endif

  typedef std::size_t size_type;
    
  BOOST_STATIC_CONSTANT(size_type, maximum_array_size =
    boost::integer_traits<size_type>::const_max);
};

// On x86-64, we can use tagged_ptr, though we will have a lower maximum
// array size here.
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

    typedef edk::tagged_ptr<T> tagged_ptr_type;

    // This is only a word.
    typedef typename tagged_ptr_type::tag_type size_type;

    BOOST_STATIC_CONSTANT(size_type, maximum_array_size =
      boost::integer_traits<size_type>::const_max);
  };
#endif

} // memory
} // edk

#endif // EDK_6AD7A71C_0953_42B4_9DE0_4904CD20178B

