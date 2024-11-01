#include <iostream>
#include <limits>
#include <string>

#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 private:
  class Node {
   public:
    Key key;
    T value;
    Node *right_;
    Node *left_;
    Node *root_;

    Node(Key key = Key(), T value = T(), Node *right_ = nullptr,
         Node *left_ = nullptr, Node *root_ = nullptr) {
      this->key = key;
      this->value = value;
      this->left_ = left_;
      this->right_ = right_;
      this->root_ = root_;
    };
  };

  Node *head;
  int Size;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  map();
  map(std::initializer_list<value_type> const &items);
  map(map &m);
  map(map &&m);
  map operator=(map &&m) {
    this->head = m->head;
    m->head = nullptr;
    return *this;
  };

  bool empty() { return !this->head; }
  size_type size() { return (size_type)this->Size; }
  size_type max_size() {
    return std::numeric_limits<size_type>::max() /
           sizeof(typename map<Key, T>::Node);
  }

  void clear();
  void swap(map &other);
  void merge(map &other);
  ~map();

  class MapIterator {
   private:
    Node *current_min;

   public:
    using iterator = class MapIterator;
    MapIterator(Node *current_min) { this->current_min = current_min; }
    Node *operator++(int) { return find_positive_next(); }
    bool operator!=(const iterator &it) {
      return current_min != it.current_min;
    }
    bool operator==(const iterator &it) {
      return current_min == it.current_min;
    }
    std::pair<Key, T> operator*() {
      return std::pair<Key, T>(current_min->key, current_min->value);
    }

    Node *find_min(Node *current_min) {
      bool break_flag = false;
      while (!break_flag) {
        if (!current_min->left_)
          break_flag = true;
        else
          current_min = current_min->left_;
      }
      return current_min;
    }
    Node *find_max(Node *current_max) {
      bool break_flag = false;
      while (!break_flag) {
        if (!current_max->right_)
          break_flag = true;
        else
          current_max = current_max->right_;
      }
      return current_max;
    }

    Node *find_positive_next() {
      Node *next_;
      if (current_min->right_)
        next_ = find_min(current_min->right_);
      else {
        Node *current_next = current_min->root_;
        bool break_flag = false;
        int min_dif = current_next->key - current_min->key;
        next_ = current_next;
        while (!break_flag) {
          if (current_min->root_->key > current_min->key) {
            if (current_next->key - current_min->key < min_dif &&
                current_next->key - current_min->key > 0) {
              min_dif = current_next->key - current_min->key;
              next_ = current_next;
            }

          } else if (current_min->root_->key < current_min->key) {
            if (current_next->key - current_min->key < -1 * min_dif &&
                current_next->key - current_min->key > 0) {
              min_dif = current_next->key - current_min->key;
              next_ = current_next;
            }
          }
          if (current_min->key < current_next->key) {
            if (current_next->left_->key == current_min->key)
              break_flag = true;
            else
              current_next = current_next->left_;
          } else if (current_min->key > current_next->key) {
            if (current_next->right_->key == current_min->key &&
                current_min->key == find_max(current_min->root_)->key) {
              break_flag = true;
              next_ = current_min->right_;
            } else if (current_next->right_->key == current_min->key)
              break_flag = true;

            else
              current_next = current_next->right_;
          }
        }
      }
      this->current_min = next_;
      return next_;
    }
  };

  Node *find_begin(Node *current) {
    if (current) {
      bool break_flag = false;
      while (!break_flag) {
        if (!current->left_)
          break_flag = true;
        else
          current = current->left_;
      }
    }
    return current;
  }

  Node *find_end(Node *current) {
    Node *result = current;
    if (current) {
      bool break_flag = false;
      while (!break_flag) {
        if (!current->right_)
          break_flag = true;
        else {
          current = current->right_;
        }
      }
      if (!this->head)
        result = this->head;
      else {
        result = current->right_;
      }
    }
    return result;
  }

  T &at(const Key &key) {
    if (key != find_eq_or_parent(key)->key) {
      throw std::out_of_range("ERROR");
    }

    return find_eq_or_parent(key)->value;
  };

  Node *find_eq_or_parent(const Key &key) {
    Node *current = this->head;
    bool break_flag = false;
    while (!break_flag && current) {
      if (key == current->key) {
        break_flag = true;
      } else if (key < current->key) {
        if (current->left_)
          current = current->left_;
        else
          break_flag = true;
      } else if (key > current->key) {
        if (current->right_)
          current = current->right_;
        else
          break_flag = true;
      }
    }
    return current;
  };

  Node *find_parent(const Key &key) {
    Node *current = this->head;
    bool break_flag = false;
    while (!break_flag && current) {
      if (key > current->key && current->right_) {
        if (current->right_->key != key) {
          current = current->right_;
        } else
          break_flag = true;
      } else if (key < current->key && current->left_) {
        if (current->left_->key != key) {
          current = current->left_;
        } else
          break_flag = true;
      }
    }
    return current;
  };

  T &operator[](const Key &key) { return this->at(key); }

  bool contains(const Key &key) {
    Node *result = find_eq_or_parent(key);
    return (key == result->key) ? true : false;
  }

  std::pair<MapIterator, bool> insert(const Key &key, const T &obj) {
    std::pair<MapIterator, bool> result(std::make_pair(nullptr, false));
    if (!this->head) {
      this->head = new Node(key, obj, nullptr, nullptr, this->head);
      result.first = this->head;
      result.second = true;
      this->Size++;
    } else {
      Node *current = find_eq_or_parent(key);
      if (key != current->key) {
        if (key < current->key) {
          current->left_ = new Node(key, obj, nullptr, nullptr, current->root_);
          result.first = current->left_;
          result.second = true;
          this->Size++;
        } else if (key > current->key) {
          current->right_ =
              new Node(key, obj, nullptr, nullptr, current->root_);
          result.first = current->right_;
          result.second = true;
          this->Size++;
        } else if (key == current->key) {
          result.first = current;
        }
      }
    }
    return result;
  }

  std::pair<MapIterator, bool> insert(const value_type &value) {
    return this->insert(value.first, value.second);
  }

  std::pair<MapIterator, bool> insert_or_assign(const Key &key, const T &obj) {
    std::pair<MapIterator, bool> result(std::make_pair(nullptr, false));
    if (!this->insert(key, obj).second) {
      this->find_eq_or_parent(key)->value = obj;
    }
    if (this->find_eq_or_parent(key)->key == key &&
        this->find_eq_or_parent(key)->value == obj) {
      result.first = find_eq_or_parent(key);
    }
    return result;
  }

  MapIterator begin() { return find_begin(this->head); }

  MapIterator end() { return find_end(this->head); }
  void erase(MapIterator pos);

  template <typename... Args>
  std::vector<std::pair<MapIterator, bool>> insert_many(Args &&...args) {
    std::vector<std::pair<MapIterator, bool>> vec;
    (vec.push_back(insert(std::forward<Args>(args))), ...);
    return vec;
  }
};
}  // namespace s21

template <typename T, typename Key>
s21::map<T, Key>::map() {
  this->head = nullptr;
  this->Size = 0;
}

template <typename T, typename Key>
s21::map<T, Key>::map(std::initializer_list<value_type> const &items) {
  this->Size = 0;
  bool break_flag = false;
  Node *current = nullptr;
  this->head = nullptr;
  for (value_type item : items) {
    if (this->head == nullptr) {
      this->head = new Node(items.begin()->first, items.begin()->second);
      this->head->root_ = this->head;
      current = this->head;
    } else {
      while (break_flag == false && current) {
        if (item.first < current->key) {
          if (!current->left_) {
            current->left_ =
                new Node(item.first, item.second, nullptr, nullptr, this->head);
            break_flag = true;
          } else
            current = current->left_;
        } else if (item.first > current->key) {
          if (!current->right_) {
            current->right_ =
                new Node(item.first, item.second, nullptr, nullptr, this->head);
            break_flag = true;
          } else
            current = current->right_;
        };
      }
      current = this->head;
      break_flag = false;
    }
    this->Size++;
  }
}

template <typename T, typename Key>
s21::map<T, Key>::map(map &m) {
  this->head = new Node(m.head->key, m.head->value, nullptr, nullptr, m.head);
  this->Size = 1;

  while (this->Size != m.Size) {
    for (auto it = MapIterator(this->begin()); it != this->end(); it++) {
      if (!this->find_eq_or_parent((*it).first)->left_ &&
          m.find_eq_or_parent((*it).first)->left_) {
        this->find_eq_or_parent((*it).first)->left_ =
            new Node(m.find_eq_or_parent((*it).first)->left_->key,
                     m.find_eq_or_parent((*it).first)->left_->value, nullptr,
                     nullptr, m.head);
        this->Size++;
      }
      if (!this->find_eq_or_parent((*it).first)->right_ &&
          m.find_eq_or_parent((*it).first)->right_) {
        this->find_eq_or_parent((*it).first)->right_ =
            new Node(m.find_eq_or_parent((*it).first)->right_->key,
                     m.find_eq_or_parent((*it).first)->right_->value, nullptr,
                     nullptr, m.head);
        this->Size++;
      }
    }
  }
}

template <typename T, typename Key>
s21::map<T, Key>::map(map &&m) {
  this->head = m.head;
  this->Size = m.Size;
  m.clear();
}

template <typename T, typename Key>
void s21::map<T, Key>::clear() {
  if (this->head) {
    bool break_flag = false;

    while (!break_flag) {
      auto it = MapIterator(this->begin());
      while (it != this->end()) {
        if (this->find_eq_or_parent((*it).first)->left_ &&
            !this->find_eq_or_parent((*it).first)->left_->left_ &&
            !this->find_eq_or_parent((*it).first)->left_->right_) {
          this->find_eq_or_parent((*it).first)->left_->root_ = nullptr;

          delete this->find_eq_or_parent((*it).first)->left_;
          this->find_eq_or_parent((*it).first)->left_ = nullptr;
          this->Size--;
        }

        if (this->find_eq_or_parent((*it).first)->right_ &&
            !this->find_eq_or_parent((*it).first)->right_->left_ &&
            !this->find_eq_or_parent((*it).first)->right_->right_) {
          this->find_eq_or_parent((*it).first)->right_->root_ = nullptr;

          delete this->find_eq_or_parent((*it).first)->right_;
          this->find_eq_or_parent((*it).first)->right_ = nullptr;
          this->Size--;
        }
        if (this->Size == 1) {
          break_flag = true;

          this->head->root_ = nullptr;
          delete this->head;
          this->head = nullptr;
          this->Size = 0;
          break;
        } else {
          it++;
        }
      }
    }
  }
}

template <typename T, typename Key>
void s21::map<T, Key>::swap(map &other) {
  Node *temp = this->head;
  size_type temp_size = this->Size;
  this->head = other.head;
  this->Size = other.Size;
  other.head = temp;
  other.Size = temp_size;
}

template <typename T, typename Key>
void s21::map<T, Key>::merge(map &other) {
  auto it = MapIterator(other.begin());
  for (; it != other.end(); it++) {
    if (!this->contains((*it).first)) {
      Node *current = other.find_eq_or_parent((*it).first);
      if (current->key == (*it).first) {
        std::cout << current->key << "key" << std::endl;
        this->insert(current->key, current->value);
        break;
      }
    }
  }
}

template <typename T, typename Key>
void s21::map<T, Key>::erase(MapIterator pos) {
  Node *current = this->find_eq_or_parent((*pos).first);
  if (current->key == (*pos).first) {
    this->Size--;
    current->left_ = nullptr;
    current->right_ = nullptr;
    current->root_ = nullptr;
    Key erased_key = (*pos).first;
    Node *parent = this->find_parent((*pos).first);
    delete current;
    if (erased_key < parent->key) {
      parent->left_ = nullptr;
    } else if (erased_key > parent->key) {
      parent->right_ = nullptr;
    }
  }
}

template <typename T, typename Key>
s21::map<T, Key>::~map() {
  this->clear();
}
