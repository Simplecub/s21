#ifndef __TREE_H__
#define __TREE_H__
#include <limits>  //max_size

// AVL-Tree
namespace s21 {
template <typename K, typename V>
class Tree {
 public:
  class Iterator;
  class ConstIterator;
  using key_type = K;
  using value_type = V;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

 protected:
  struct Node  // структура для представления узлов дерева
  {
    key_type key_;
    value_type value_;
    int height_ = 0;
    Node *left_ = nullptr;
    Node *right_ = nullptr;
    Node *parent_ = nullptr;
    Node(key_type key, value_type value) : key_(key), value_(value){};
    Node(key_type key, value_type value, Node *node)
        : key_(key), value_(value), parent_(node){};
    friend class Tree<K, V>;
  };

 public:
  Node *root_;
  class Iterator {
   public:
    Iterator() : current_(nullptr), prev_(nullptr){};
    Iterator(Node *node, Node *prev_node = nullptr)
        : current_(node), prev_(prev_node){};
    Iterator &operator++();    // Префиксный инкремент
    Iterator operator++(int);  // Постфиксный инкремент
    Iterator &operator--();
    Iterator operator--(int);
    Iterator &operator-=(size_type n) {
      while (n-- > 0) operator--();
      return *this;
    };
    Iterator &operator+=(size_type n) {
      while (n-- > 0) operator++();
      return *this;
    };
    reference operator*();
    bool operator==(const iterator &other) {
      return current_ == other.current_;
    };
    bool operator!=(const iterator &other) {
      return current_ != other.current_;
    };
    friend class Tree;
    friend class ConstIterator;
    Node *current_;
    Node *prev_;
    Node *GoForward(Node *node);
    Node *GoBack(Node *node);
  };
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
  };

 public:
  // Constructors
  Tree() : root_(nullptr){};
  Tree(const Tree &other) { root_ = CopyTree(other.root_, nullptr); };
  // Конструктор перемещения
  Tree(Tree &&other);
  // Destructor
  ~Tree();
  // Оператор присваивания с перемещением
  Tree &operator=(Tree &&other) noexcept;
  // Оператор присваивания с копированием
  Tree &operator=(const Tree &other);
  // Methods
  iterator begin() { return Tree::Iterator(GetMinNode(root_)); };
  iterator end();
  bool empty() { return root_ == nullptr; };
  size_type size() { return GetRecursiveSize(root_); };
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const K &key);
  iterator multiInsert_(const K &key);
  void erase(iterator pos);
  void swap(Tree &other) { std::swap(root_, other.root_); };
  void merge(Tree &other);
  bool contains(const K &key) {
    return !((RecursiveFind(root_, key) == nullptr));
  };

 protected:
  // Method support functions
  Node *CopyTree(Tree::Node *node, Tree::Node *parent);
  size_type GetRecursiveSize(Tree::Node *node);
  static Node *GetMaxNode(Tree::Node *node);
  static Node *GetMinNode(Tree::Node *node);
  void RecursiveFreeALLNodes(Node *node);
  iterator Find(const K &key);
  Node *RecursiveFind(Tree::Node *node, const K &key);
  bool RecursiveInsert(Tree::Node *node, const K &key, V value);
  bool RecursiveMultiInsert(Tree::Node *node, const K &key, V value);
  iterator FindLastInserted(Node *node, const K &key) const;
  Node *RecursiveDelete(Tree::Node *node, K key);

  // Balance functions
  void Balance(Node *node);
  void RotateLeft(Node *node);
  void RotateRight(Node *node);
  int GetHeightNode(Node *node);
  void SetHeightNode(Node *node);
  int GetBalanceNode(Node *node);
};

//// Constructors ////
template <typename K, typename V>
Tree<K, V>::Tree(Tree &&other) {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(const Tree &other) {
  if (this != &other) {
    Tree temp(other);
    delete root_;
    *this = std::move(temp);
  }
  return *this;
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(Tree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

//// Destructor ////
template <typename K, typename V>
Tree<K, V>::~Tree() {
  clear();
}

//// Methods ////
template <typename K, typename V>
typename Tree<K, V>::Iterator Tree<K, V>::end() {
  if (root_ == nullptr) return begin();
  Node *last_node = GetMaxNode(root_);
  Iterator res(nullptr, last_node);
  return res;
}

template <typename K, typename V>
size_t Tree<K, V>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename Tree<K, V>::Node);
}

template <typename K, typename V>
void Tree<K, V>::clear() {
  if (root_ != nullptr) RecursiveFreeALLNodes(root_);
  root_ = nullptr;
}

template <typename K, typename V>
std::pair<typename Tree<K, V>::iterator, bool> Tree<K, V>::insert(
    const K &key) {
  std::pair<Iterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new Node(key, key);
    return std::pair<Iterator, bool>(iterator(root_), true);
  } else {
    bool is_insert = RecursiveInsert(root_, key, key);
    return std::pair<Iterator, bool>(Find(key), is_insert);
  }
}

template <typename K, typename V>
typename Tree<K, V>::iterator Tree<K, V>::multiInsert_(const K &key) {
  if (root_ == nullptr) {
    root_ = new Node(key, key);
    return Iterator(root_);
  } else {
    RecursiveMultiInsert(root_, key, key);
    // Возвращаем итератор на последний вставленный элемент.
    return FindLastInserted(root_, key);
  }
}

template <typename K, typename V>
void Tree<K, V>::erase(iterator pos) {
  if (root_ == nullptr || pos.current_ == nullptr) return;
  root_ = RecursiveDelete(root_, *pos);
}

template <typename K, typename V>
void Tree<K, V>::merge(Tree &other) {
  std::vector<K> keys;
  // Итерация по other и сбор ключей в вектор
  for (Iterator it = other.begin(); it != other.end(); ++it) {
    keys.push_back(*it);
  }
  // Вставка каждого ключа в текущее дерево и удаление из other.
  for (const auto &key : keys) {
    insert(key);
    other.erase(other.Find(key));
  }
}

//// Iterator ////
template <typename K, typename V>
typename Tree<K, V>::Iterator &Tree<K, V>::Iterator::operator++() {
  Node *tmp;
  if (current_ != nullptr) {
    tmp = GetMaxNode(current_);
  }
  current_ = GoForward(current_);
  if (current_ == nullptr) {
    prev_ = tmp;
  }
  return *this;
}

template <typename K, typename V>
typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename K, typename V>
typename Tree<K, V>::Iterator &Tree<K, V>::Iterator::operator--() {
  if (current_ == nullptr && prev_ != nullptr) {
    *this = prev_;
    return *this;
  }
  current_ = GoBack(current_);
  return *this;
}

template <typename K, typename V>
typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator--(int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename K, typename V>
V &Tree<K, V>::Iterator::operator*() {
  if (current_ == nullptr) {
    static V fake_value{};
    return fake_value;
  }
  return current_->key_;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::Iterator::GoBack(Tree::Node *node) {
  if (node->left_ != nullptr) {
    // Если есть левое поддерево, идем в самый правый узел этого поддерева
    return GetMaxNode(node->left_);
  }
  // Если нет левого поддерева, ищем первый родитель, у которого мы не были
  // левым потомком
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  // Возвращаем первого родителя, у которого мы были правым потомком
  return parent;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::Iterator::GoForward(Tree::Node *node) {
  if (node->right_ != nullptr) {
    // Если есть правое поддерево, идем в самый левый узел этого поддерева
    return GetMinNode(node->right_);
  }
  // Если нет правого поддерева, ищем первый родитель, у которого мы не были
  // правым потомком
  Node *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  // Возвращаем первого родителя, у которого мы были левым потомком
  return parent;
}

//// Support functions ////

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::CopyTree(Tree::Node *node,
                                                Tree::Node *parent) {
  if (node == nullptr) return nullptr;
  Node *new_node = new Node(node->key_, node->value_, parent);
  new_node->left_ = CopyTree(node->left_, new_node);
  new_node->right_ = CopyTree(node->right_, new_node);
  return new_node;
}
template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::GetMaxNode(Tree::Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->right_ == nullptr) {
    return node;
  }
  return GetMaxNode(node->right_);
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::GetMinNode(Tree::Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  if (node->left_ == nullptr) {
    return node;
  }
  return GetMinNode(node->left_);
}

template <typename K, typename V>
void Tree<K, V>::RecursiveFreeALLNodes(Node *node) {
  if (node == nullptr) return;
  RecursiveFreeALLNodes(node->left_);
  RecursiveFreeALLNodes(node->right_);
  delete node;
}

template <typename K, typename V>
typename Tree<K, V>::iterator Tree<K, V>::Find(const K &key) {
  Node *exact_node = RecursiveFind(root_, key);
  return Iterator(exact_node);
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::RecursiveFind(Tree::Node *node,
                                                     const K &key) {
  if (node == nullptr || node->key_ == key) return node;
  if (key > node->key_)
    return RecursiveFind(node->right_, key);
  else
    return RecursiveFind(node->left_, key);
}

template <typename K, typename V>
bool Tree<K, V>::RecursiveInsert(Tree::Node *node, const K &key, V value) {
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new Node(key, value, node);
      SetHeightNode(node);
      Balance(node);
      return true;
    }
    if (RecursiveInsert(node->left_, key, value)) {
      SetHeightNode(node);
      Balance(node);
      return true;
    }
  } else if (key > node->key_) {
    if (node->right_ == nullptr) {
      node->right_ = new Node(key, value, node);
      SetHeightNode(node);
      Balance(node);
      return true;
    }
    if (RecursiveInsert(node->right_, key, value)) {
      SetHeightNode(node);
      Balance(node);
      return true;
    }
  } else {
    return false;  // ключ уже существует
  }
  return false;
}

template <typename K, typename V>
bool Tree<K, V>::RecursiveMultiInsert(Tree::Node *node, const K &key, V value) {
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new Node(key, value, node);
      SetHeightNode(node);
      Balance(node);
      return true;
    }
    if (RecursiveMultiInsert(node->left_, key, value)) {
      SetHeightNode(node);
      Balance(node);
      return true;
    }
  } else {  // ключи могут быть равны в multiset
    if (node->right_ == nullptr) {
      node->right_ = new Node(key, value, node);
      SetHeightNode(node);
      Balance(node);
      return true;
    }
    if (RecursiveMultiInsert(node->right_, key, value)) {
      SetHeightNode(node);
      Balance(node);
      return true;
    }
  }
  return false;
}

template <typename K, typename V>
typename Tree<K, V>::Iterator Tree<K, V>::FindLastInserted(Node *node,
                                                           const K &key) const {
  iterator it = nullptr;
  while (node != nullptr) {
    if (key < node->key_) {
      node = node->left_;
    } else {
      it = Iterator(node);  // сохраняем текущий узел
      node = node->right_;
    }
  }
  return it;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::RecursiveDelete(Tree::Node *node,
                                                       K key) {
  if (node == nullptr) return nullptr;

  if (key < node->key_) {
    node->left_ = RecursiveDelete(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = RecursiveDelete(node->right_, key);
  } else {
    // Узел найден
    if (node->left_ == nullptr) {
      Node *right_child = node->right_;
      if (right_child != nullptr) right_child->parent_ = node->parent_;
      delete node;
      return right_child;
    } else if (node->right_ == nullptr) {
      Node *left_child = node->left_;
      if (left_child != nullptr) left_child->parent_ = node->parent_;
      delete node;
      return left_child;
    } else {
      Node *min_in_right = GetMinNode(node->right_);
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right_ = RecursiveDelete(node->right_, min_in_right->key_);
    }
  }

  SetHeightNode(node);
  Balance(node);
  return node;
}

template <typename K, typename V>
size_t Tree<K, V>::GetRecursiveSize(Tree::Node *node) {
  if (node == nullptr) return 0;
  return 1 + GetRecursiveSize(node->left_) + GetRecursiveSize(node->right_);
}

//// Balance ////
// При  разбалансировке (GetBalanceNode(node) == 2(правая ветвь больше) или -2
// (левая ветвь больше))
// а) Если правая ветвь больше(2) и если у правого поддерева левая ветвь длиннее
//(баланс <0), то сначала на нем малое правое вращение, затем малое левое на
// самом узле б) Если левая ветвь больше(-2) и  если у правого поддерева правая
// ветвь длиннее (баланс >0), то сначала малое левое вращение, затем малое
// правое на самомм узле
template <typename K, typename V>
void Tree<K, V>::Balance(Node *node) {
  if (GetBalanceNode(node) == 2) {
    if (GetBalanceNode(node->right_) < 0) {
      RotateRight(node->right_);
    }
    RotateLeft(node);

  } else if (GetBalanceNode(node) == -2) {
    if (GetBalanceNode(node->left_) > 0) {
      RotateLeft(node->left_);
    }
    RotateRight(node);
  }
}

template <typename K, typename V>
void Tree<K, V>::RotateLeft(Node *node) {
  Node *new_root = node->right_;
  node->right_ = new_root->left_;

  if (new_root->left_) {
    new_root->left_->parent_ = node;
  }

  new_root->parent_ = node->parent_;

  if (!node->parent_) {
    root_ = new_root;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = new_root;
  } else {
    node->parent_->right_ = new_root;
  }

  new_root->left_ = node;
  node->parent_ = new_root;

  SetHeightNode(node);
  SetHeightNode(new_root);
}

template <typename K, typename V>
void Tree<K, V>::RotateRight(Node *node) {
  // новый корень поддерева
  Node *new_root = node->left_;
  // обновление левого дочернего узла
  node->left_ = new_root->right_;

  if (new_root->right_) {
    new_root->right_->parent_ = node;
  }
  // обновление родителя нового узла
  new_root->parent_ = node->parent_;
  // обновление родителя текущего узла
  if (!node->parent_) {
    root_ = new_root;
  } else if (node == node->parent_->right_) {
    node->parent_->right_ = new_root;
  } else {
    node->parent_->left_ = new_root;
  }
  // перемещение текущего узла вниз
  new_root->right_ = node;
  node->parent_ = new_root;

  SetHeightNode(node);
  SetHeightNode(new_root);
}

template <typename K, typename V>
int Tree<K, V>::GetHeightNode(Node *node) {
  return node == nullptr ? 0 : node->height_;
}

template <typename K, typename V>
void Tree<K, V>::SetHeightNode(Node *node) {
  node->height_ =
      1 + std::max(GetHeightNode(node->left_), GetHeightNode(node->right_));
}

template <typename K, typename V>
int Tree<K, V>::GetBalanceNode(Node *node) {
  return node == nullptr
             ? 0
             : GetHeightNode(node->right_) - GetHeightNode(node->left_);
}

}  // namespace s21

#endif  // __TREE_H__