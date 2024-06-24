#ifndef S21_TREE_H
#define S21_TREE_H

#include <iostream>
#include <limits>
#include <utility>

#include "../vector/vector.h"

namespace s21 {
template <typename K, typename V>
class Tree {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  Tree() noexcept;
  explicit Tree(const value_type &elem) noexcept;
  Tree(std::initializer_list<value_type> const &items);
  Tree(const Tree &other) noexcept;
  Tree(Tree &&other) noexcept;
  ~Tree();

  Tree &operator=(const Tree &other) noexcept;
  Tree &operator=(Tree &&other) noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  void clear() noexcept;
  void swap(Tree &other);
  void merge(Tree<K, V> &other);
  // bool contains(const key_type &key) const noexcept;

 protected:
  typedef struct Node {
    value_type data_ = value_type{};
    Node *parent_ = nullptr;
    Node *left_ = nullptr;
    Node *right_ = nullptr;

    Node(const value_type &elem) : data_(elem) {}
    ~Node() = default;
  } Node;

  void insert_(Node *&root_, K key, V value);
  void push_(K key, V value);
  bool contains(const key_type &key) const noexcept;
  void clear_node(Node *node);

  class Iterator {
   public:
    Iterator(Node *first, const Tree<K, V> &second) noexcept
        : current_(first), tree_(&second) {}
    Iterator(const Iterator &other) {
      current_ = other.current_;
      tree_ = other.tree_;
    }
    ~Iterator() = default;

    bool operator==(const Iterator &other) {
      return this->current_ == other.current_;
    }
    bool operator!=(const Iterator &other) {
      return this->current_ != other.current_;
    }
    value_type *operator->() { return &(current_->data_); }
    key_type operator*() {
      // return current_ ? current_->data_ : const_reference{};
      return current_ ? current_->data_.first
                      : static_cast<key_type>(tree_->size());
    }

    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);

    Iterator operator=(const Iterator &other) {
      current_ = other.current_;
      return *this;
    }

    Node *Get() { return current_; }

   protected:
    Node *current_;
    const Tree<K, V> *tree_;

   private:
    void increase_();
    void decrease_();
    Node *find_parent_(Node *node);
    Node *find_leftmost_(Node *node);
    Node *find_rightmost_(Node *node);
    Node *max_();
    Node *min_();
  };

  Iterator find_pos_(const key_type &key) noexcept;
  bool is_multi_set = false;

 public:
  using const_iterator = const Iterator;
  using iterator = Iterator;

  iterator begin() const;
  iterator end() const;
  void erase(iterator pos);

  template <class... Args>
  Vector<std::pair<typename Tree<key_type, mapped_type>::iterator, bool>>
  insert_many(Args &&...args);

 private:
  Node *root_ = nullptr;
  size_type size_ = 0;
  size_type max_size_;
};

template <typename K, typename V>
Tree<K, V>::Tree() noexcept {}

template <typename K, typename V>
Tree<K, V>::Tree(const value_type &elem) noexcept {
  push_(elem.first, elem.second);
}

template <typename K, typename V>
Tree<K, V>::Tree(const std::initializer_list<value_type> &items) {
  if (items.size() == 0) return;
  for (auto &item : items) {
    push_(item.first, item.second);
  }
}

template <typename K, typename V>
Tree<K, V>::Tree(const Tree &other) noexcept {
  *this = other;
}

template <typename K, typename V>
Tree<K, V>::Tree(Tree &&other) noexcept {
  // *this = std::move(other);
  this->swap(other);
}

template <typename K, typename V>
Tree<K, V>::~Tree() {
  clear();
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(const Tree &other) noexcept {
  if (this != &other) {
    // this->clear();
    for (iterator it = other.begin(); it != other.end(); it++) {
      this->push_(it->first, it->second);
    }
  }
  return *this;
}

template <typename K, typename V>
Tree<K, V> &Tree<K, V>::operator=(Tree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    this->size_ = other.size_;
    other.clear();
  }
  return *this;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::size() const noexcept {
  return size_;
}

template <typename K, typename V>
void Tree<K, V>::clear() noexcept {
  if (root_ != nullptr) {
    clear_node(root_);
  }
  root_ = nullptr;
  size_ = 0;
}

template <typename K, typename V>
inline void Tree<K, V>::swap(Tree &other) {
  std::swap(root_, other.root_);
  std::swap(size_, other.size_);
  std::swap(max_size_, other.max_size_);
}

template <typename K, typename V>
inline void Tree<K, V>::erase(iterator pos) {
  Node *cur = pos.Get();
  if (cur->left_ == nullptr && cur->right_ == nullptr &&
      cur->parent_ == nullptr) {
    delete cur;
    root_ = nullptr;
    size_--;
    return;
  }
  if (cur->left_ == nullptr && cur->right_ == nullptr) {
    // если нет детей
    if (cur->parent_->left_ == cur) {
      cur->parent_->left_ = nullptr;
    } else {
      cur->parent_->right_ = nullptr;
    }
    delete cur;
    size_--;
  } else if (cur->left_ != nullptr && cur->right_ != nullptr) {
    // если есть оба ребенка... и ипотека
    Node *min = cur->right_;
    while (min->left_ != nullptr) {
      min = min->left_;
    }
    min->parent_ = cur->parent_;
    min->left_ = cur->left_;
    if (min != cur->right_) {
      min->right_ = cur->right_;
    } else {
      min->right_ = nullptr;
    }
    if (cur->parent_->left_ == cur) {
      cur->parent_->left_ = min;
    } else {
      cur->parent_->right_ = min;
    }
    if (root_ == cur) {
      root_ = min;
    }
    delete cur;
    size_--;
  } else {
    // один из детей есть
    Node *tmp;
    if (cur->left_ != nullptr) {
      tmp = cur->left_;
    } else {
      tmp = cur->right_;
    }
    if (cur->parent_ && cur->parent_->left_ == cur) {
      cur->parent_->left_ = tmp;
    }
    if (cur->parent_ && cur->parent_->right_ == cur) {
      cur->parent_->right_ = tmp;
    }
    tmp->parent_ = cur->parent_;
    if (root_ == cur) {
      root_ = tmp;
    }
    delete cur;
    size_--;
  }
}

template <typename K, typename V>
bool Tree<K, V>::empty() const noexcept {
  return !root_;
}

template <typename K, typename V>
typename Tree<K, V>::size_type Tree<K, V>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Tree<V, V>) / 6;
}

template <typename K, typename V>
inline V &Tree<K, V>::at(const key_type &key) {
  for (iterator it = this->begin(); it != this->end(); it++) {
    if (it->first == key) {
      return it->second;
    }
  }
  throw std::out_of_range("Key not found");
}

template <typename K, typename V>
inline V &Tree<K, V>::operator[](const key_type &key) {
  if (!contains(key)) {
    push_(key, V());
  }
  return at(key);
}

template <typename K, typename V>
void Tree<K, V>::merge(Tree<K, V> &other) {
  if (other.root_ == nullptr || this->root_ == other.root_) return;
  if (this->root_ == nullptr) swap(other);

  iterator it = other.begin();
  iterator it_erase = other.begin();
  while (it != other.end()) {
    ++it;
    if (!contains(it_erase->first) || is_multi_set) {
      push_(it_erase->first, it_erase->second);
      other.erase(it_erase);
    }
    it_erase = it;
  }
}

template <typename K, typename V>
void Tree<K, V>::insert_(Node *&node_, K key, V value) {
  if (key <= node_->data_.first) {
    if (node_->left_ == nullptr) {
      node_->left_ = new Node({key, value});
      node_->left_->parent_ = node_;
    } else {
      insert_(node_->left_, key, value);
    }
  } else if (key > node_->data_.first) {
    if (node_->right_ == nullptr) {
      node_->right_ = new Node({key, value});
      node_->right_->parent_ = node_;
    } else {
      insert_(node_->right_, key, value);
    }
  }
}

template <typename K, typename V>
void Tree<K, V>::push_(K key, V value) {
  if (!empty() && (contains(key) && !is_multi_set)) {
    return;
  }
  if (this->root_ == nullptr) {
    this->root_ = new Node({key, value});
  } else {
    insert_(this->root_, key, value);
  }
  this->size_++;
}

template <typename K, typename V>
inline bool Tree<K, V>::contains(const key_type &key) const noexcept {
  for (iterator it = this->begin(); it != this->end(); ++it) {
    if (it->first == key) {
      return true;
    }
  }
  return false;
}

template <typename K, typename V>
void Tree<K, V>::clear_node(Node *node) {
  if (node->left_ != nullptr) {
    clear_node(node->left_);
  }
  if (node->right_ != nullptr) {
    clear_node(node->right_);
  }
  delete node;
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::find_pos_(
    const key_type &key) noexcept {
  for (iterator it = this->begin(); it != this->end(); ++it) {
    if (it->first == key) {
      return it;
    }
  }
  return end();
}

template <typename K, typename V>
inline typename Tree<K, V>::iterator Tree<K, V>::begin() const {
  if (this->root_ == nullptr) {
    return iterator(nullptr, *this);
  }
  Node *tmp_node = root_;
  while (tmp_node->left_ != nullptr) {
    tmp_node = tmp_node->left_;
  }
  iterator tmp(tmp_node, *this);
  return tmp;
}

template <typename K, typename V>
inline typename Tree<K, V>::iterator Tree<K, V>::end() const {
  return Iterator(nullptr, *this);
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator++() {
  increase_();
  return *this;
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator++(int) {
  Iterator tmp(*this);
  increase_();
  return tmp;
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator--() {
  decrease_();
  return *this;
}

template <typename K, typename V>
inline typename Tree<K, V>::Iterator Tree<K, V>::Iterator::operator--(int) {
  Iterator tmp(*this);
  decrease_();
  return tmp;
}

template <typename K, typename V>
inline void Tree<K, V>::Iterator::increase_() {
  if (current_ == nullptr) {
    current_ = find_parent_(tree_->begin().Get());
    current_ = find_rightmost_(current_);
  } else if (current_ == max_()) {
    current_ = nullptr;
  } else {
    if (current_->right_ != nullptr) {
      current_ = current_->right_;
      current_ = find_leftmost_(current_);
    } else {
      while (current_->parent_ != nullptr &&
             current_->data_.first > current_->parent_->data_.first) {
        current_ = current_->parent_;
      }
      if (current_->parent_ != nullptr) current_ = current_->parent_;
    }
  }
}

template <typename K, typename V>
inline void Tree<K, V>::Iterator::decrease_() {
  if (current_ == nullptr) {
    current_ = find_parent_(tree_->begin().Get());
    current_ = find_rightmost_(current_);
  } else if (current_ == min_()) {
    current_ = nullptr;
  } else {
    if (current_->left_ != nullptr) {
      current_ = current_->left_;
      current_ = find_rightmost_(current_);
    } else {
      while (current_->parent_ != nullptr &&
             current_->data_.first < current_->parent_->data_.first) {
        current_ = current_->parent_;
      }
      if (current_->parent_ != nullptr) current_ = current_->parent_;
    }
  }
}

template <typename K, typename V>
inline typename Tree<K, V>::Node *Tree<K, V>::Iterator::find_parent_(
    Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  while (node->parent_ != nullptr) {
    node = node->parent_;
  }
  return node;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::Iterator::find_leftmost_(Node *node) {
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

template <typename K, typename V>
typename Tree<K, V>::Node *Tree<K, V>::Iterator::find_rightmost_(Node *node) {
  if (node == nullptr) {
    return nullptr;
  }
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

template <typename K, typename V>
inline typename Tree<K, V>::Node *Tree<K, V>::Iterator::max_() {
  Node *tmp_max = find_parent_(current_);
  tmp_max = find_rightmost_(tmp_max);
  return tmp_max;
}

template <typename K, typename V>
inline typename Tree<K, V>::Node *Tree<K, V>::Iterator::min_() {
  Node *tmp_min = find_parent_(current_);
  tmp_min = find_leftmost_(tmp_min);
  return tmp_min;
}

template <typename key_type, typename mapped_type>
template <typename... Args>
Vector<std::pair<typename Tree<key_type, mapped_type>::iterator, bool>>
Tree<key_type, mapped_type>::insert_many(Args &&...args) {
  Vector<std::pair<typename Tree<key_type, mapped_type>::iterator, bool>> ret;
  ret.second = true;
  for (auto arg : {args...}) {
    if (contains(arg)) {
      ret.second = false;
    } else {
      Tree<key_type, mapped_type>::push_(arg);
      ret.first = Tree<key_type, mapped_type>::find_pos_(arg);
    }
  }
  return ret;
}

}  // namespace s21

#endif  // S21_TREE_H_