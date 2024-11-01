#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#include <iostream>

// using namespace std;

namespace s21 {
template <class T>
class VectorIterator;

template <class T>
class VectorConstIterator;

template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = VectorIterator<T>;
  using const_iterator = VectorConstIterator<T>;
  using size_type = size_t;
  using pointer = T *;

  // constructors & destructor
  vector() { this->set_zero(); };

  vector(size_type n) {
    if (this->max_size() < n)
      throw std::out_of_range("Size is bigger then max_size()");
    if (n <= 0) throw std::out_of_range("Index out of range");
    this->size_ = n;
    this->capacity_ = n;
    this->container_ = new value_type[n];
  };

  vector(std::initializer_list<value_type> const &items) {
    this->capacity_ = this->size_ = items.size();
    if (this->size_) {
      this->container_ = new value_type[this->size_];
      std::copy(items.begin(), items.end(), this->container_);
    } else {
      this->set_zero();
    }
  }

  vector(const vector &v) noexcept {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->container_ = new value_type[this->size_];
    for (size_type i = 0; i < this->size_; i++)
      this->container_[i] = v.container_[i];
  }

  vector(vector &&v) noexcept {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->container_ = v.container_;
    v.set_zero();
  }

  ~vector() {
    if (this->container_) delete[] this->container_;
    this->set_zero();
  }

  vector &operator=(vector &&v) {
    if (this->container_) delete[] this->container_;
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    this->container_ = v.container_;
    v.set_zero();
    delete[] v.container_;
    return *this;
  }

  vector &operator=(const vector &v) {
    if (this != &v) {
      this->size_ = v.size_;
      this->capacity_ = v.capacity_;
      this->container_ = new value_type[this->size_];
      for (size_t i = 0; i < size(); i++) this->container_[i] = v.container_[i];
    }
    return *this;
  }

  // Vector Iterators
  iterator begin() { return iterator(container_); }
  iterator end() { return iterator(container_ + size_); }
  const_iterator cbegin() const { return const_iterator(container_); }
  const_iterator cend() const { return iterator(container_ + size_); }

  // Vector Capacity

  bool empty() const { return size_ == 0; }
  size_type size() const { return size_; }
  size_type capacity() const { return capacity_; }

  size_type max_size() const {
    int bits = 63;
    if (sizeof(void *) == 4) bits = 31;
    return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
  }

  void shrink_to_fit() {
    if (capacity_ > size_) this->set_memory(size_);
  }

  void reserve(size_type size) {
    size_type zero = 0;
    if (zero > size) throw std::out_of_range("Index out of range");
    if (size > capacity_) this->set_memory(size);
  }

  // Vector Modifiers

  void clear() { this->size_ = 0; };
  void pop_back() {
    if (this->size_ > 0) size_--;
  }
  void swap(vector &other) {
    std::swap(other.size_, this->size_);
    std::swap(other.capacity_, this->capacity_);
    std::swap(other.container_, this->container_);
  }

  iterator insert(iterator pos, const_reference value) {
    size_type elem_pos = &(*pos) - container_;
    size_type zero = 0;
    if (zero > elem_pos || elem_pos >= size_ + 1)
      throw std::out_of_range("Index out of range");
    if (size_ == capacity_) reserve(capacity_ * 2);
    size_++;
    for (size_type i = size_ - 1; i > elem_pos; i--)
      container_[i] = container_[i - 1];
    container_[elem_pos] = value;

    return container_ + elem_pos;
  }

  void erase(iterator pos) {
    size_type zero = 0;
    size_type elem_pos = &(*pos) - container_;
    if (zero > elem_pos || elem_pos >= size_)
      throw std::out_of_range("Pos out of range");
    for (size_type i = elem_pos + 1; i < size_; i++)
      container_[i - 1] = container_[i];
    this->pop_back();
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) this->set_memory(capacity_ * 2);
    size_++;
    container_[size_ - 1] = value;
  }

  // Vector Elements access
  reference at(size_type pos) {
    size_type zero = 0;
    if (zero > pos || pos >= size())
      throw std::out_of_range("Index out of range");
    return container_[pos];
  }
  const_reference front() const { return *container_; }
  const_reference back() const { return *(container_ + size_ - 1); }
  reference operator[](size_type pos) {
    size_type zero = 0;
    if (zero > pos || pos >= size())
      throw std::out_of_range("Index out of range");
    return container_[pos];
  }

  pointer data() { return container_; }
  // helpers
  void set_zero() {
    this->size_ = 0;
    this->capacity_ = 0;
    this->container_ = nullptr;
  }

  void set_memory(size_type size) {
    value_type *tmp = container_;
    for (size_type i = 0; i < size_; i++) tmp[i] = container_[i];
    container_ = new value_type[size];
    for (size_type i = 0; i < size_; i++) container_[i] = tmp[i];
    delete[] tmp;
    capacity_ = size;
  }

  // extra
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  iterator insert_many(iterator pos, Args &&...args) {
    iterator pos_ = pos;
    auto elems = {std::forward<Args>(args)...};
    for (auto it = std::make_reverse_iterator(elems.end()),
              rend = std::make_reverse_iterator(elems.begin());
         it != rend; ++it) {
      pos_ = insert(pos_, std::move(*it));
    }
    return pos_;
  }

 private:
  size_type size_;
  size_type capacity_;
  value_type *container_;
};

template <class T>
class VectorIterator {
  friend class vector<T>;
  friend class VectorConstIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorIterator() { ptr_ = nullptr; }
  VectorIterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --(*this);
    return tmp;
  }

  VectorIterator operator+(const size_t value) {
    VectorIterator tmp(this->ptr_ + value);
    return tmp;
  }

  VectorIterator operator-(const size_t value) {
    VectorIterator tmp(this->ptr_ - value);
    return tmp;
  }

  bool operator==(const VectorIterator &other) { return ptr_ == other.ptr_; }

  bool operator!=(const VectorIterator &other) { return ptr_ != other.ptr_; }

  operator VectorConstIterator<T>() const {
    return VectorConstIterator<T>(ptr_);
  }

 private:
  pointer ptr_;
};

template <class T>
class VectorConstIterator {
  friend class vector<T>;
  friend class VectorIterator<T>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  VectorConstIterator() { ptr_ = nullptr; };
  VectorConstIterator(pointer ptr) { ptr_ = ptr; };
  value_type operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  VectorConstIterator &operator++() {
    ptr_++;
    return *this;
  }

  VectorConstIterator &operator--() {
    ptr_--;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  VectorConstIterator operator--(int) {
    VectorConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const VectorConstIterator &other) {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const VectorConstIterator &other) {
    return ptr_ != other.ptr_;
  }

  operator VectorIterator<T>() const { return VectorIterator<T>(ptr_); }

 private:
  pointer ptr_;
};
}  // namespace s21
   // namespace s21

#endif