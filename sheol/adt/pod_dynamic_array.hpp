////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_8F2F2234_B763_4A5D_A070_AE378D3E8E18)
#define SHEOL_8F2F2234_B763_4A5D_A070_AE378D3E8E18

#include <memory>
#include <algorithm>
#include <cstring>

#include <boost/config.hpp>
#include <boost/swap.hpp>
#include <boost/assert.hpp>
#include <boost/detail/iterator.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/spirit/home/support/container.hpp>

#include <sheol/config.hpp>
#include <sheol/adt/policy/power_growth_policy.hpp>

namespace sheol {
namespace adt {

template <typename T, std::size_t Initial = 8,
          typename Alloc = std::allocator<T>,
          typename GrowthPolicy = power_growth_policy<2>::apply<T> >
struct pod_dynamic_array {
  typedef T value_type;
  typedef T& reference;
  typedef T const& const_reference;
  typedef T* pointer;
  typedef T const* const_pointer;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  typedef T* iterator;
  typedef T const* const_iterator;

  typedef Alloc allocator_type;

  typedef GrowthPolicy growth_policy_type;

  void construct (size_type init = Initial) {
    // TODO: Make this an exception.
    BOOST_ASSERT(init != 0);
    size_ = 0;
    capacity_ = init;
    data_ = Alloc().allocate(init);
  }

  void construct (pod_dynamic_array const& other) {
    size_ = 0;
    capacity_ = 0;
    data_ = 0;
    copy(other.begin(), other.end());
  }

  template <typename Container>
  typename boost::enable_if<
    boost::spirit::traits::is_container<Container>
  >::type construct (Container const& c) {
    size_ = 0;
    capacity_ = 0;
    data_ = 0;
    copy(c.begin(), c.end());
  }

  template <typename Iterator>
  void construct (Iterator first, Iterator last) {
    size_ = 0;
    capacity_ = 0;
    data_ = 0;
    copy(first, last);
  }

  void destroy (void) {
    clear();
    if (data_ && (capacity_ != 0))
      Alloc().deallocate(data_, capacity_);
    size_ = 0;
    capacity_ = 0;
    data_ = 0;
  }
  
  void swap (pod_dynamic_array& other) {
    boost::swap(*this, other);
  }

  void assign (pod_dynamic_array const& other) {
    if (*this != other)
      copy(other.begin(), other.end());
  }

  template <typename Container>
  void assign (Container const& c) {
    if (*this != c)
      copy(c.begin(), c.end());
  }

  template <typename Iterator>
  void assign (Iterator first, Iterator last) {
    if (std::equal(first, last, data_))
      copy(first, last);
  }

  size_type size (void) const
  { return size_; }

  size_type capacity (void) const
  { return capacity_; }

  bool empty (void) const
  { return size_ == 0; }

  void clear (void) {
    if (data_ && (size_ != 0)) {
      for (size_type i = 0; i < size_; ++i)
        Alloc().destroy(&data_[i]);
      size_ = 0;  
    }
  }

  void push_back (T const& val) {
    if (size_ == capacity_) {
      typename boost::result_of<GrowthPolicy(size_type, size_type)>::type
        new_capacity = gp_(capacity_, size_);  
  
      // allocate the new block
      T* new_data = Alloc().allocate(new_capacity); 
  
      // copy the old data
      std::memcpy(new_data, data_, size_ * sizeof(T)); 
  
      // destroy and deallocate old data  
      for (size_type i = 0; i < size_; ++i)
        Alloc().destroy(&data_[i]);
      if (capacity_)
        Alloc().deallocate(data_, capacity_);
  
      data_ = new_data;
      capacity_ = new_capacity;
    }
  
    Alloc().construct(&data_[size_], val);
    size_ += 1;
  }
 
  void pop_back (void) {
    Alloc().destroy(&data_[size_ - 1]);
    size_ -= 1;
  }

  iterator begin (void) {
    return &data_[0];
  }

  const_iterator begin (void) const {
    return &data_[0];
  }

  const_iterator cbegin (void) const {
    return &data_[0];
  }

  iterator end (void) {
    return &data_[size_];
  }

  const_iterator end (void) const {
    return &data_[size_];
  }

  const_iterator cend (void) const {
    return &data_[size_];
  }

  reference front (void) {
    return data_[0];
  }

  const_reference front (void) const {
    return data_[0];
  }

  const_reference cfront (void) const {
    return data_[0];
  }
     
  reference back (void) {
    return data_[size_ - 1];
  }

  const_reference back (void) const {
    return data_[size_ - 1];
  }

  const_reference cback (void) const {
    return data_[size_ - 1];
  }
        
  reference operator[] (size_type i) {
    return data_[i];
  }

  const_reference operator[] (size_type i) const {
    return data_[i];
  }

  void reserve (size_type s) {
    if (capacity_ != s) {
      T* new_data = Alloc().allocate(s); // allocate the new block
  
      if (size_) {
        if (size_ > s)
          std::memcpy(new_data, data_, size_ * sizeof(T)); 
        else 
          std::memcpy(new_data, data_, s * sizeof(T));
      }
  
      // destroy and deallocate old data  
      for (size_type i = 0; i < size_; ++i) {
        Alloc().destroy(&data_[i]);
      }
  
      if (capacity_)
        Alloc().deallocate(data_, capacity_);
  
      if (size_ > s)
        size_ = s;
  
      data_ = new_data;
      capacity_ = s; 
    } 
  }

  template <typename Container>
  bool operator== (Container const& c) const {
    return (size_ == c.size()) && std::equal(c.begin(), c.end(), &data_[0]);
  }

  template <typename Container>
  bool operator!= (Container const& c) const {
    return !operator==(c);
  }

  template <typename Iterator>
  void copy (Iterator first, Iterator last) {
    typename boost::detail::iterator_traits<Iterator>::difference_type
      dist = boost::detail::distance(first, last);
  
    clear();
  
    if (first == last)
      return;
  
    // deallocate the old data and reallocate a big enough array
    if (dist > capacity_) {
      if (data_ && (capacity_ != 0))
        Alloc().deallocate(data_, capacity_);
  
      // figure out how large we need the array to be
      while (dist > capacity_)
        capacity_ = gp_(capacity_, size_type(0));
  
      // allocate it
      data_ = Alloc().allocate(capacity_);
    }
  
    for (size_ = 0; first != last; ++first, ++size_) {
      Alloc().construct(&data_[size_], *first);
    }
  }

  size_type size_;
  size_type capacity_;
  GrowthPolicy gp_;
  T* data_;
};

} // adt
} // sheol

#endif // SHEOL_8F2F2234_B763_4A5D_A070_AE378D3E8E18

