#ifndef __LIST_H__
#define __LIST_H__

#include <iostream>
#include <limits>  //max_size
#include <utility>

namespace s21 {
template <typename T>
class list {
 public:
  // member types
  using value_type = T;  // определяет тип элемента (T — параметр шаблона)
  using reference = T &;  // T &определяет тип ссылки на элемент
  using const_reference = const T &;  // определяет тип постоянной ссылки
  // определяет тип размера контейнера (стандартный тип — size_t)
  using size_type = size_t;

 private:
  typedef struct Node {
    T data = T();
    Node *next_;
    Node *prev_;
    explicit Node(T value = T(), Node *next_ = nullptr,
                  Node *prev_ = nullptr) noexcept
        : data(value),
          next_(next_),
          prev_(prev_) {}  // явный вызов конструктора
  } Node;

  Node *head_;
  Node *tail_;
  Node *end_;
  size_type size_ = 0;

  template <typename T1>
  class ListConstIterator {
   public:
    ListConstIterator(){};
    ListConstIterator(list::Node *node) noexcept : current_(node) {}

    const_reference operator*() const { return current_->data; }

    ListConstIterator &operator++() noexcept {
      current_ = current_->next_;
      return *this;
    }
    ListConstIterator &operator--() noexcept {
      current_ = current_->prev_;
      return *this;
    }
    bool operator==(const ListConstIterator &other) const noexcept {
      return current_ == other.current_;
    }
    bool operator!=(const ListConstIterator &other) const noexcept {
      return current_ != other.current_;
    }
    Node *current_;
  };

  using const_iterator = ListConstIterator<T>;

  template <typename T1>
  class ListIterator {
   public:
    operator ListConstIterator<T1>() const {
      return ListConstIterator<T1>(current_);
    }

    ListIterator(){};
    explicit ListIterator(list::Node *node) noexcept : current_(node) {}

    T &operator*() { return current_->data; }

    ListIterator &operator++() noexcept {
      current_ = current_->next_;
      return *this;
    }
    ListIterator &operator--() noexcept {
      current_ = current_->prev_;
      return *this;
    }
    bool operator==(const ListIterator &other) const noexcept {
      return current_ == other.current_;
    }
    bool operator!=(const ListIterator &other) const noexcept {
      return current_ != other.current_;
    }

    Node *current_;
  };

 public:
  using iterator = ListIterator<T>;
  // Constructors
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  list(list &&l);
  // Destructor
  ~list();
  list &operator=(const list &l);
  list &operator=(list &&l) noexcept;
  // Method //
  // List Element access
  const_reference front() const noexcept {
    return head_ ? head_->data : end_->data;
  };
  const_reference back() const noexcept {
    return tail_ ? tail_->data : front();
  };
  // List Iterators
  iterator begin() const { return iterator(head_ ? head_ : end_); };
  iterator end() const { return iterator(end_); };
  const_iterator cbegin() const { return const_iterator(head_ ? head_ : end_); }
  const_iterator cend() const { return const_iterator(end_); }
  // List Capacity
  bool empty() const { return size_ == 0; };
  size_type size() const noexcept { return size_; };
  size_type max_size();
  // List Modifiers
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();
  // вставляет новые элементы в контейнер непосредственно перед pos
  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  // добавляет новые элементы в конец контейнер
  template <class... Args>
  void insert_many_back(Args &&...args);
  // добавляет новые элементы в верхнюю часть контейнера
  template <class... Args>
  void insert_many_front(Args &&...args);
};

//// Constructors ////
template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {
  end_ = new Node(T(), nullptr, nullptr);
}

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  if (n <= 0) throw std::out_of_range("list size must be positive");
  end_ = new Node(T(), nullptr, nullptr);
  while (n > 0) {
    push_back(T());
    n--;
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  end_ = new Node(T(), nullptr, nullptr);
  for (value_type item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list &l) : head_(nullptr), tail_(nullptr), size_(0) {
  end_ = new Node(T(), nullptr, nullptr);
  if (this != &l) {
    for (const auto &it : l) {
      push_back(it);
    }
  }
}

template <typename T>
list<T>::list(list &&l) {
  if (this != &l) {
    clear();
    head_ = l.head_;
    tail_ = l.tail_;
    size_ = l.size_;
    end_ = l.end_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.end_ = nullptr;
    l.size_ = 0;
  }
}

template <typename T>
list<T> &list<T>::operator=(const list &l) {
  if (this != &l) {
    clear();
    head_ = nullptr;
    tail_ = nullptr;
    for (const auto &item : l) {
      push_back(item);
    }
  }
  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    if (end_) delete end_;
    head_ = l.head_;
    tail_ = l.tail_;
    end_ = l.end_;
    size_ = l.size_;
    l.head_ = nullptr;
    l.tail_ = nullptr;
    l.size_ = 0;
    l.end_ = nullptr;
  }
  return *this;
}

//// Destructor ////
template <typename T>
list<T>::~list() {
  clear();
  // delete head_;
  head_ = nullptr;
  // delete tail_;
  tail_ = nullptr;
  delete end_;
  end_ = nullptr;
}

//// Methods ////
template <typename T>
typename list<T>::size_type list<T>::max_size() {
  size_t nodeSize = sizeof(typename list<T>::Node);
  size_t maxNodes = std::numeric_limits<size_type>::max() / nodeSize;
  return maxNodes;
}

template <typename T>
void list<T>::clear() noexcept {
  while (size_ != 0) pop_front();
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node *newNode = new Node(value);

  newNode->prev_ = pos.current_->prev_;
  if (pos.current_->prev_)
    pos.current_->prev_->next_ = newNode;
  else {
    head_ = newNode;
  }
  pos.current_->prev_ = newNode;

  newNode->next_ = pos.current_;

  if (pos.current_ == tail_) tail_ = newNode;

  --pos;  // Возвращаем итератор на вставленный элемент
  ++size_;
  return pos;
}

template <typename T>
void s21::list<T>::erase(iterator pos) {
  if (pos.current_ == nullptr) {
    return;
  }

  if (pos.current_->prev_ != nullptr) {
    pos.current_->prev_->next_ = pos.current_->next_;
  } else {
    head_ = pos.current_->next_;
  }

  if (pos.current_->next_ != nullptr) {
    pos.current_->next_->prev_ = pos.current_->prev_;
  } else {
    tail_ = pos.current_->prev_;
  }

  delete pos.current_;
  pos.current_ = nullptr;
  --size_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  if (!head_) {
    head_ = new Node(value, nullptr, nullptr);
    head_->next_ = end_;
    end_->prev_ = head_;

  } else if (!tail_) {
    tail_ = new Node(value, nullptr, nullptr);
    tail_->next_ = end_;
    tail_->prev_ = head_;
    end_->prev_ = tail_;
    head_->next_ = tail_;

  } else {
    Node *temp_ = new Node(value, nullptr, nullptr);
    temp_->prev_ = tail_;
    tail_->next_ = temp_;
    tail_ = temp_;

    end_->prev_ = tail_;
    tail_->next_ = end_;
  }
  size_++;
}

template <typename T>
void list<T>::pop_back() {
  if (tail_) {
    Node *tail_rm = tail_;
    if (tail_->prev_ != end_) {
      tail_ = tail_->prev_;
    } else {
      tail_ = nullptr;
    }

    if (tail_rm->prev_) delete tail_rm;

    if (size_ == 2) {
      end_->next_ = head_;
      end_->prev_ = head_;
      head_->next_ = end_;
      head_->prev_ = end_;
      tail_ = nullptr;
    }
    --size_;
    end_->data = size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  if (!head_) {
    head_ = new Node(value, end_, end_);
    end_->prev_ = head_;
    end_->next_ = head_;
  } else if (!tail_) {
    tail_ = head_;
    tail_->next_ = end_;
    tail_->prev_ = new Node(value, nullptr, nullptr);
    end_->prev_ = tail_;
    end_->next_ = nullptr;
    tail_->prev_->next_ = tail_;

    head_ = tail_->prev_;

  } else

  {
    Node *temp_ = new Node(value, nullptr, nullptr);
    head_->prev_ = temp_;
    temp_->next_ = head_;
    temp_->prev_ = nullptr;
    head_ = temp_;
  }
  size_++;
}

template <typename T>
void list<T>::pop_front() {
  if (head_ == nullptr) {
    throw std::out_of_range("list is empty");
  } else {
    Node *temp = this->head_;
    this->head_ = head_->next_;
    delete temp;
  }
  size_--;
}

template <typename T>
void list<T>::swap(list &other) {
  if (this != &other) {
    Node *temp_h = head_;
    Node *temp_t = tail_;
    Node *temp_e = end_;
    size_t temp_size = other.size_;

    if (other.head_ || head_) {
      head_ = other.head_;
      other.head_ = temp_h;
    }
    if (other.tail_ || tail_) {
      tail_ = other.tail_;
      other.tail_ = temp_t;
    }
    if (other.end_ || end_) {
      end_ = other.end_;
      other.end_ = temp_e;
    }
    other.size_ = size_;
    size_ = temp_size;
  }
}

template <typename T>
void list<T>::merge(list &other) {
  if (other.head_) {
    if (this->size_ == 0) {
      this->swap(other);

    } else if (this != &other) {
      s21::list<T> temp;
      auto it_o = other.begin();
      auto it = begin();
      while (it_o != other.end() && (it != end())) {
        if (*it_o < *it) {
          temp.push_back(*it_o);
          ++it_o;
        } else {
          temp.push_back(*it);
          ++it;
        }
      }

      while (it_o != other.end()) {
        temp.push_back(*it_o);
        ++it_o;
      }
      while (it != this->end()) {
        temp.push_back(*it);
        ++it;
      }

      other.clear();
      clear();
      this->swap(temp);
      temp.clear();
    }
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this != &other) {
    iterator temp = iterator(pos.current_);
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      insert(temp, *iter);
    }
    // other.clear();
  }
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node *current = head_;
    Node *prev = nullptr;
    Node *next = nullptr;
    tail_ = head_;
    while (current != end_) {
      next = current->next_;
      current->next_ = prev;
      current->prev_ = next;
      prev = current;
      current = next;
    }
    head_ = prev;

    end_->prev_ = tail_;
    tail_->next_ = end_;
  }
}

template <typename T>
void list<T>::unique() {
  if (head_ == nullptr) {
    return;
  }
  auto it = begin();
  auto next_it = ++begin();
  s21::list<T> temp;

  temp.push_back(*it);
  while (next_it != end()) {
    if (*it == *next_it) {
      ++next_it;
    } else {
      temp.push_back(*next_it);
      it = next_it;
      ++next_it;
    }
  }
  this->swap(temp);
  temp.clear();
}

template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    bool isSorted = true;
    auto it = begin();
    auto next = it;
    ++next;

    while (isSorted) {
      isSorted = false;
      it = begin();
      next = it;
      ++next;
      while (next != end()) {
        if (*it > *next) {
          isSorted = true;
          auto temp = *it;
          *it = *next;
          *next = temp;
        }
        ++it;
        ++next;
      }
    }
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  auto pos_ = pos;
  // Свертка с запятой
  (insert(ListIterator<T>(pos_.current_), std::forward<Args>(args)), ...);
  return ListIterator<T>(pos_.current_);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  (push_front(std::forward<Args>(args)), ...);
}

}  // namespace s21

#endif  // __LIST_H__