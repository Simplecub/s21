#ifndef QUEUE_H
#define QUEUE_H

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  // default constructor
  queue() : container_() {}
  // init members constructor
  queue(std::initializer_list<value_type> const &items) : container_(items) {}
  // copy constructor
  queue(const queue &q) : container_(q.container_) {}
  // move constructor
  queue(queue &&q) noexcept : container_(std::move(q.container_)) {}
  // destructor
  ~queue() = default;

  // copy assignment operator
  queue &operator=(const queue &q) {
    if (this != &q) container_ = q.container_;
    return *this;
  }

  // move assignment operator
  queue &operator=(queue &&q) noexcept {
    if (this != &q) container_ = std::move(q.container_);
    return *this;
  }

  // other functions
  const_reference front() const { return container_.front(); }
  const_reference back() const { return container_.back(); }
  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }
  void push(const_reference value) { container_.push_back(value); }
  void pop() { container_.pop_front(); }  // removes first element
  void swap(queue &other) { std::swap(container_, other.container_); }

  // extra
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(args), ...);
  }

 private:
  Container container_;
};
}  // namespace s21

#endif
