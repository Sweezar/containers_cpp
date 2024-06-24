#ifndef S21_SET_H
#define S21_SET_H

#include <iostream>
#include <utility>

#include "../tree/tree.h"
#include "../vector/vector.h"

namespace s21 {

template <typename Value>
class Set : public Tree<Value, Value> {
 public:
  using key_type = Value;
  using value_type = Value;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  Set() : Tree<key_type, value_type>(){};
  Set(std::initializer_list<value_type> const &items);
  Set(const Set &s) : Tree<key_type, value_type>(s){};
  Set(Set &&s) : Tree<key_type, value_type>(std::move(s)){};
  ~Set() = default;
  Set &operator=(Set &&s);

  using iterator = typename Tree<key_type, value_type>::iterator;
  using const_iterator = typename Tree<key_type, value_type>::const_iterator;

  bool operator==(const iterator &it);
  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(Set &other);
  void merge(Set &other);

  iterator find(const key_type &key);

  bool contains(const key_type &key);

  template <class... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename value_type>
inline Set<value_type>::Set(std::initializer_list<value_type> const &items)
    : Tree<value_type, value_type>() {
  // Tree<value_type, value_type>();
  for (const auto &item : items) {
    insert(item);
  }
}

template <typename value_type>
inline Set<value_type> &Set<value_type>::operator=(Set<value_type> &&s) {
  Tree<value_type, value_type>::operator=(std::move(s));
  return *this;
}

template <typename value_type>
inline typename Set<value_type>::iterator Set<value_type>::begin() {
  return Tree<value_type, value_type>::begin();
}

template <typename value_type>
inline typename Set<value_type>::iterator Set<value_type>::end() {
  return Tree<value_type, value_type>::end();
}

template <typename value_type>
inline bool Set<value_type>::empty() {
  return Tree<value_type, value_type>::empty();
}

template <typename value_type>
inline typename Set<value_type>::size_type Set<value_type>::size() {
  return Tree<value_type, value_type>::size();
}

// TODO: выяснить, как возвращать максимальный размер правильно
template <typename value_type>
inline typename Set<value_type>::size_type Set<value_type>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename Tree<value_type, value_type>::Node) / 2;
}

template <typename value_type>
inline typename std::pair<typename Set<value_type>::iterator, bool>
Set<value_type>::insert(const value_type &value) {
  if (Tree<value_type, value_type>::contains(value) &&
      !Tree<value_type, value_type>::is_multi_set) {
    iterator pos = Tree<value_type, value_type>::find_pos_(value);

    return std::pair<iterator, bool>(pos, false);
  }

  Tree<value_type, value_type>::push_(value, value);
  iterator pos = Tree<value_type, value_type>::find_pos_(value);

  return std::pair<iterator, bool>(pos, true);
}

template <typename value_type>
void Set<value_type>::clear() {
  Tree<value_type, value_type>::clear();
}

template <typename value_type>
void Set<value_type>::erase(iterator pos) {
  this->Tree<value_type, value_type>::erase(pos);
}

template <typename value_type>
void Set<value_type>::swap(Set &other) {
  Tree<value_type, value_type>::swap(other);
}

template <typename value_type>
void Set<value_type>::merge(Set &other) {
  Tree<value_type, value_type>::merge(other);
}

template <typename value_type>
typename Set<value_type>::iterator Set<value_type>::find(const key_type &key) {
  return Tree<value_type, value_type>::find_pos_(key);
}

template <typename value_type>
bool Set<value_type>::contains(const key_type &key) {
  return Tree<value_type, value_type>::contains(key);
}

template <typename value_type>
template <class... Args>
Vector<std::pair<typename Set<value_type>::iterator, bool>>
Set<value_type>::insert_many(Args &&...args) {
  Vector<std::pair<typename Tree<value_type, value_type>::iterator, bool>> ret;
  for (auto arg : {args...}) {
    if (contains(arg) && !Tree<value_type, value_type>::is_multi_set) {
      ret.push_back(
          std::pair(Tree<value_type, value_type>::find_pos_(arg), false));
    } else {
      Tree<value_type, value_type>::push_(arg, arg);
      ret.push_back(
          std::pair(Tree<value_type, value_type>::find_pos_(arg), true));
    }
  }

  return ret;
}

}  // namespace s21
#endif
