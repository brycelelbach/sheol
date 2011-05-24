////////////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file BOOST_LICENSE_1_0.rst or copy at http://www.boost.org/LICENSE_1_0.txt)
////////////////////////////////////////////////////////////////////////////////

#if !defined(SHEOL_3CAF1ACA_C212_4FA5_AB0A_CD511F24E24B)
#define SHEOL_3CAF1ACA_C212_4FA5_AB0A_CD511F24E24B

#include <algorithm>

#include <boost/swap.hpp>
#include <boost/noncopyable.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/iterator/iterator_facade.hpp>

#include <sheol/config.hpp>

namespace sheol {
namespace adt {

template <typename T>
struct pod_doubly_linked_list_node {
  typedef pod_doubly_linked_list_node* pointer;

  pod_doubly_linked_list_node (T const& val_, pointer next_, pointer prev_):
    val(val_), next(next_), prev(prev_) { }

  pod_doubly_linked_list_node (pod_doubly_linked_list_node const& other):
    val(other.val), next(other.next), prev(other.prev) { }

  void unlink (void) {
    prev->next = next;
    next->prev = prev;
  }

  T val;
  pod_doubly_linked_list_node* next;
  pod_doubly_linked_list_node* prev;
};

template <typename T, typename Enable = void>
struct pod_doubly_linked_list_iterator;

template <typename T>
struct pod_doubly_linked_list_iterator<T, typename boost::enable_if<
  boost::is_const<T>
>::type>: boost::iterator_facade<
  pod_doubly_linked_list_iterator<T>, T, boost::bidirectional_traversal_tag
> {
  typedef pod_doubly_linked_list_node<
    typename boost::remove_const<T>::type
  > const node_type;

  typedef pod_doubly_linked_list_iterator<
    typename boost::remove_const<T>::type
  > other_type;

  pod_doubly_linked_list_iterator (void): curr(0), prev(0) { }

  pod_doubly_linked_list_iterator (node_type* curr_, node_type* prev_):
    curr(curr_), prev(prev_) { }

  pod_doubly_linked_list_iterator (pod_doubly_linked_list_iterator const& it):
    curr(it.curr), prev(it.prev) { }
   
  pod_doubly_linked_list_iterator (other_type const& other):
    curr(other.curr), prev(other.prev) { }

  void increment (void) {
    if (curr != 0) { // not at end
      prev = curr;
      curr = curr->next;
    }
  }

  void decrement (void) {
    if (prev != 0) { // not at begin
      curr = prev;
      prev = prev->prev;
    }
  }

  template <typename Iterator>
  bool equal (Iterator const& other) const {
    return curr == other.curr;
  }

  typename pod_doubly_linked_list_iterator::reference
  dereference (void) const {
    return curr->val;
  }

  node_type* curr;
  node_type* prev;
};

template <typename T>
struct pod_doubly_linked_list_iterator<T, typename boost::disable_if<
  boost::is_const<T>
>::type>: boost::iterator_facade<
  pod_doubly_linked_list_iterator<T>, T, boost::bidirectional_traversal_tag
> {
  typedef pod_doubly_linked_list_node<T> node_type;

  pod_doubly_linked_list_iterator (void): curr(0), prev(0) { }

  pod_doubly_linked_list_iterator (node_type* curr_, node_type* prev_):
    curr(curr_), prev(prev_) { }

  pod_doubly_linked_list_iterator (pod_doubly_linked_list_iterator const& it):
    curr(it.curr), prev(it.prev) { }

  void increment (void) {
    if (curr != 0) { // not at end
      prev = curr;
      curr = curr->next;
    }
  }

  void decrement (void) {
    if (prev != 0) { // not at begin
      curr = prev;
      prev = prev->prev;
    }
  }

  template <typename Iterator>
  bool equal (Iterator const& other) const {
    return curr == other.curr;
  }

  typename pod_doubly_linked_list_iterator::reference
  dereference (void) const {
    return curr->val;
  }

  node_type* curr;
  node_type* prev;
};

template <typename T, typename Alloc = std::allocator<T> >
struct pod_doubly_linked_list {
  typedef T value_type;
  typedef T& reference;
  typedef T const& const_reference;
  typedef T* pointer;
  typedef T const* const_pointer;
  typedef std::size_t size_type;

  typedef pod_doubly_linked_list_iterator<T> iterator;
  typedef pod_doubly_linked_list_iterator<T const> const_iterator;
  
  typedef pod_doubly_linked_list_node<T> node_type; 

  typedef typename Alloc::template rebind<node_type>::other allocator_type;

  void construct (void) {
    first = last = 0;
  }
 
  void construct (pod_doubly_linked_list const& other) {
    first = last = 0;
    assign(other);
  }
  
  template <typename Iterator>
  void construct (Iterator it, Iterator end) {
    first = last = 0;
    assign(it, end);
  }

  void assign (pod_doubly_linked_list const& other) {
    clear();
    node_type* p = other.first;
  
    while (p != 0) {
      push_back(p->val);
      p = p->next;
    }
  }

  template <typename Iterator>
  void assign (Iterator it, Iterator end) {
    clear();
    
    for (; it != end; ++it)
      push_back(*it); 
  } 

  void clear (void) {
    if (first == last) { // we only have one element
      if (first) {
        allocator_type().destroy(first);
        allocator_type().deallocate(first, 1);
      }
      return;
    }
  
    node_type* p = first;
    
    while (p) {
      node_type* next = p->next;
      allocator_type().destroy(p);
      allocator_type().deallocate(p, 1);
      p = next;
    } 
  
    first = last = 0;
  }

  void swap (pod_doubly_linked_list& other) {
    boost::swap(*this, other);
  }

  void insert (T const& val, iterator pos) {
    if (!pos.curr) {
      push_back(val);
      return;
    }
  
    node_type* new_node = allocator_type().allocate(1);
    allocator_type().construct
      (new_node, node_type(val, pos.curr, pos.curr->prev));
  
    if (pos.curr->prev)
      pos.curr->prev->next = new_node;
    else
      first = new_node;
  
    pos.curr->prev = new_node;
  }

  void push_front (T const& val) {
    node_type* new_node;
  
    if (first == 0) {
      new_node = allocator_type().allocate(1);
      allocator_type().construct(new_node, node_type(val, 0, 0));
      first = last = new_node;
    }
  
    else {
      new_node = allocator_type().allocate(1);
      allocator_type().construct(new_node, node_type(val, first, first->prev));
      first->prev = new_node;
      first = new_node;
    }
  }

  void push_back (T const& val) {
    if (last == 0) push_front(val);
  
    else {
      node_type* new_node = allocator_type().allocate(1);
      allocator_type().construct(new_node, node_type(val, last->next, last));

      last->next = new_node;
      last = new_node;
    }
  }

  void pop_front (void) {
    if (!first) return;
  
    else if (first == last) { // there's only one item
      allocator_type().destroy(first);
      allocator_type().deallocate(first, 1);
      first = last = 0;
    }
  
    else {
      node_type* np = first;
      first = first->next;
      first->prev = 0;
      allocator_type().destroy(np);
      allocator_type().deallocate(np, 1);
    }
  }

  void pop_back (void) {
    if (!first) return;
  
    else if (first == last) { // there's only one item
      allocator_type().destroy(first);
      allocator_type().deallocate(first, 1);
      first = last = 0;
    }
  
    else {
      node_type* np = last;
      last = last->prev;
      last->next = 0;
      allocator_type().destroy(np);
      allocator_type().deallocate(np, 1);
    }
  }

  iterator begin (void) {
    return iterator(first, 0);
  }

  const_iterator begin (void) const {
    return const_iterator(first, 0);
  }

  const_iterator cbegin (void) const {
    return const_iterator(first, 0);
  }

  iterator end (void) {
    return iterator(0, last);
  }

  const_iterator end (void) const {
    return const_iterator(0, last);
  }

  const_iterator cend (void) const {
    return const_iterator(0, last);
  }

  iterator erase (iterator pos) {
    if (pos.curr == 0)
      return iterator(0, last);
  
    else if (pos.curr == first) {
      pop_front();
      return iterator(first, 0);
    }
  
    else if (pos.curr == last) {
      pop_back();
      return iterator(0, last);
    }
  
    node_type* next(pos.curr->next);
    pos.curr->unlink();
    allocator_type().destroy(pos.curr);
    allocator_type().deallocate(pos.curr, 1);
    return iterator(next, next->prev);
  }

  bool empty (void) const
  { return first == 0 && last == 0; }

  template <typename Container>
  bool operator== (Container const& c) const {
    return std::equal(begin(), end(), c.begin());
  }

  template <typename Container>
  bool operator!= (Container const& c) const {
    return !operator==(c);
  }

  node_type* first;
  node_type* last;
};

} // adt
} // sheol

#endif // SHEOL_3CAF1ACA_C212_4FA5_AB0A_CD511F24E24B
 
