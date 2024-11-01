
#ifndef __SET_H__
#define __SET_H__

#include "s21_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set : public Tree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<Key, Key>::Iterator;
  using const_iterator = typename Tree<Key, Key>::ConstIterator;
  using size_type = size_t;
  // Constructors
  set() : Tree<Key, Key>(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &s) : Tree<Key, Key>(s){};
  set(set &&s) noexcept : Tree<Key, Key>(std::move(s)){};
  // Destructor
  ~set() = default;
  set &operator=(set &&s) noexcept;

  // Methods
  iterator find(const Key &key) { return Tree<Key, Key>::Find(key); };
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<iterator, bool>> res;
    (res.push_back(s21::Tree<int, int>::insert(std::forward<Args>(args))), ...);
    return res;
  }
};

//// Constructors ////
template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) {
  for (value_type i : items) Tree<Key, Key>::insert(i);
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&s) noexcept {
  if (this != &s) {
    Tree<Key, Key>::operator=(std::move(s));
  }
  return *this;
}

}  // namespace s21

#endif  // __SET_H__
