////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_3CCD6BB9_0A6A_4E50_82AB_747A2D705ECE)
#define SHEOL_3CCD6BB9_0A6A_4E50_82AB_747A2D705ECE

#include <boost/spirit/home/support/container.hpp>

#include <sheol/adt/pod_doubly_linked_list.hpp>

namespace sheol {
namespace adt {

template <typename T, typename Alloc = std::allocator<T> >
struct doubly_linked_list: pod_doubly_linked_list<T, Alloc> {
  typedef pod_doubly_linked_list<T> base_type;

 private:
  // Adjust type access.
  using base_type::node_type;
  using base_type::allocator_type;

  // Adjust method access.
  using base_type::construct;

  // Adjust data access;
  using base_type::first;
  using base_type::last;

 public:
  doubly_linked_list (void)
  { base_type::construct(); }

  doubly_linked_list (doubly_linked_list const& other)
  { base_type::construct(other); }

  template <typename Container>
  doubly_linked_list (Container const& c, typename boost::enable_if<
                        boost::spirit::traits::is_container<Container>
                      >::type* dummy = 0)
  { base_type::construct(c.begin(), c.end()); }

  template <typename Iterator>
  doubly_linked_list (Iterator first, Iterator last)
  { base_type::construct(first, last); }

  ~doubly_linked_list (void)
  { base_type::clear(); }

  doubly_linked_list& operator= (doubly_linked_list const& other) {
    base_type::copy(other);
    return *this;
  }

  template <typename Container>
  doubly_linked_list& operator= (Container const& c) {
    base_type::copy(c.begin(), c.end());
    return *this;
  }
};

} // adt
} // sheol

#endif // SHEOL_3CCD6BB9_0A6A_4E50_82AB_747A2D705ECE

