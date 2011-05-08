////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_7336C077_C5BF_4FFF_9A8F_B4F35ADF57E4)
#define SHEOL_7336C077_C5BF_4FFF_9A8F_B4F35ADF57E4

#include <sheol/adt/pod_dynamic_array.hpp>

namespace sheol {
namespace adt {

template <typename T, std::size_t Initial = 8,
          typename Alloc = std::allocator<T>,
          typename GrowthPolicy = power_growth_policy<2>::apply<T> >
struct dynamic_array: pod_dynamic_array<T, Initial, Alloc, GrowthPolicy> {
  typedef pod_tagged_ptr<T> base_type;

 private:
  // Adjust method access.
  using base_type::construct;
  using base_type::destroy;
  using base_type::copy;

  // Adjust data access;
  using base_type::size_;
  using base_type::capacity_;
  using base_type::alloc_;
  using base_type::gp_;
  using base_type::data_;

 public:
  dynamic_array (typename base_type::size_type init = Initial)
  { base_type::construct(init); }

  dynamic_array (dynamic_array const& other)
  { base_type::construct(other); }

  template <typename Container>
  dynamic_array (Container const& c, typename boost::enable_if<
                   boost::spirit::traits::is_container<Container>
                 >::type* dummy = 0)
  { base_type::construct(c); }

  template <typename Iterator>
  dynamic_array (Iterator first, Iterator last)
  { base_type::construct(first, last); }

  ~dynamic_array (void) {
    base_type::destroy();
  }

  dynamic_array& operator= (dynamic_array const& other) {
    base_type::copy(other.begin(), other.end());
    return *this;
  }

  template <typename Container>
  dynamic_array& operator= (Container const& c) {
    base_type::assign(c.begin(), c.end());
    return *this;
  }
};

} // adt
} // sheol

#endif // SHEOL_7336C077_C5BF_4FFF_9A8F_B4F35ADF57E4

