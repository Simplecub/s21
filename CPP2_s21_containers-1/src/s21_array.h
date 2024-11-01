#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // Array Member functions
  array(){};
  array(std::initializer_list<value_type> const &items) {
    this->size_ = items.size();
    std::copy(items.begin(), items.end(), this->container_);
  }
  array(const array &a) {
    this->size_ = a.size_;
    std::copy(a.container_, a.container_ + a.size_, this->container_);
  }

  array(array &&a) {
    std::move(a.container_, a.container_ + a.size_, this->container_);
    this->size_ = a.size_;
    a.size_ = 0;
  }
  ~array() = default;

  array &operator=(array &&a) {
    this->size_ = a.size_;
    std::move(a.container_, a.container_ + a.size_, this->container_);
    a.size_ = 0;
    return *this;
  }
  array &operator=(const array &a) {
    if (this != &a) {
      this->size_ = a.size_;
      std::copy(a.container_, a.container_ + a.size_, this->container_);
    }
    return *this;
  }
  // Array Element access
  reference at(size_type pos) {
    size_type zero = 0;
    if (zero > pos || pos >= size_)
      throw std::out_of_range("Index out of range");
    return container_[pos];
  }

  reference operator[](size_type pos) { return container_[pos]; }

  const_reference front() { return container_[0]; }

  const_reference back() { return container_[size_ - 1]; }

  iterator data() { return begin(); }

  // Array Iterators

  iterator begin() { return container_; }

  iterator end() { return container_ + size_; }

  // Array Capacity
  bool empty() { return !size_; }

  size_type size() { return size_; }

  size_type max_size() { return size(); }

  // Array Modifiers
  void swap(array &other) {
    if (this->size_ != other.size_)
      throw std::length_error("Size must be equal");
    for (size_type i = 0; i < size_; i++)
      std::swap(this->container_[i], other.container_[i]);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; i++) container_[i] = value;
  }

 private:
  value_type container_[N];
  size_type size_ = N;
};

}  // namespace s21

#endif