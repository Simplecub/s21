
#ifndef __MULTISET_H__
#define __MULTISET_H__
#include <vector>

#include "s21_tree.h"

namespace s21 {
template <typename Key>
class multiset : public Tree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename Tree<Key, Key>::Iterator;
  using const_iterator = const typename Tree<Key, Key>::Iterator;
  using size_type = size_t;
  // Constructors
  multiset() : Tree<Key, Key>(){};
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms) : Tree<Key, Key>(ms){};
  multiset(multiset&& ms) noexcept : Tree<Key, Key>(std::move(ms)){};
  // Destructor
  ~multiset() = default;

  // Methods
  iterator find(const Key& key) { return Tree<Key, Key>::Find(key); };
  iterator insert(const value_type& value);
  void merge(multiset& other);
  size_type count(const Key& key);
  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);  // >=
  iterator upper_bound(const Key& key);  // >

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> res;
    (res.push_back(std::pair(insert(std::forward<Args>(args)), true)), ...);
    return res;
  }
};

//// Constructors ////
template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  for (value_type i : items) insert(i);
}

//// Methods ////
template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  return Tree<Key, Key>::multiInsert_(value);
};

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  iterator it = other.begin();
  iterator itEnd = other.end();

  for (; it != itEnd; ++it) insert(*it);
  other.clear();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  auto it = Tree<Key, Key>::begin();
  auto end = Tree<Key, Key>::end();
  size_type count = 0;
  while (it != end && *it != key) {
    it++;
  }
  while (it != end && *(it++) == key) {
    count++;
  }

  return count;
};

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
};

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  auto it = Tree<Key, Key>::begin();
  auto end = Tree<Key, Key>::end();
  while (it != end) {
    if (*it >= key) {
      return it;
    }
    it++;
  }
  return end;
};

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  auto it = Tree<Key, Key>::begin();
  auto end = Tree<Key, Key>::end();
  while (it != end) {
    if (*it > key) {
      return it;
    }
    it++;
  }
  return end;
};

}  // namespace s21

#endif  //  __MULTISET_H__