#ifndef STACK_H
#define STACK_H

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // default constructor
  stack() : container_() {}
  // init members constructor
  stack(std::initializer_list<value_type> const &items) : container_(items) {}
  // copy constructor
  stack(const stack &s) : container_(s.container_) {}
  // move constructor
  stack(stack &&s) noexcept : container_(std::move(s.container_)) {}
  // destructor
  ~stack() = default;

  // copy assignment operator
  stack &operator=(const stack &s) {
    if (this != &s) container_ = s.container_;
    return *this;
  }

  // move assignment operator
  stack &operator=(stack &&s) noexcept {
    if (this != &s) container_ = std::move(s.container_);
    return *this;
  }

  // other functions
  const_reference top() const { return container_.back(); }
  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_back(); }
  void swap(stack &other) { std::swap(container_, other.container_); }

  // extra
  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push(args), ...);
  }

 private:
  Container container_;
};
}  // namespace s21

#endif
