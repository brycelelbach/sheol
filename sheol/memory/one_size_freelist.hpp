////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_46679152_BC54_4B33_92A7_252AA339067D)
#define SHEOL_46679152_BC54_4B33_92A7_252AA339067D

#include <boost/noncopyable.hpp>

#include <sheol/memory/pod_one_size_freelist.hpp> 

namespace sheol {
namespace memory {

template <std::size_t ObjectSize /* bytes */,
          typename Alloc = std::allocator<sheol::storage<ObjectSize> > >
struct one_size_freelist: pod_one_size_freelist<ObjectSize, Alloc>
                        , boost::noncopyable
{
  typedef pod_one_size_freelist<ObjectSize, Alloc> base_type;

 private:
  // Adjust access to data.
  using base_type::first;
  using base_type::last;
  using base_type::size_;

  // Adjust access to methods.
  using base_type::construct;

 public:
  one_size_freelist (typename base_type::size_type prealloc = 0) {
    base_type::construct();
    base_type::reserve(prealloc);
  }

  ~one_size_freelist (void) {
    base_type::clear();
  }  
};

} // memory
} // sheol

#endif // SHEOL_46679152_BC54_4B33_92A7_252AA339067D

