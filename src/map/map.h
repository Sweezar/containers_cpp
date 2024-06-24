#ifndef S21_MAP_H
#define S21_MAP_H

#include <utility>

#include "../tree/tree.h"

namespace s21 {

template <typename K, typename T>
class Map : public Tree<K, T> {
 public:
  using key_type = K;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<K, T>::iterator;
  using const_iterator = typename Tree<K, T>::const_iterator;
  using size_type = size_t;

  Map() : Tree<K, T>(){};
  Map(std::initializer_list<value_type> const &items) : Tree<K, T>(items){};
  Map(const Map &m) : Tree<K, T>(m){};
  Map(Map &&m) : Tree<K, T>(std::move(m)){};
  ~Map() = default;
  Map operator=(const Map &&m);

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key, const T &obj);
  void erase(iterator pos);
  void swap(Map &other);
  void merge(Map &other);

  bool contains(const key_type &key) const;

  template <class... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename K, typename T>
inline Map<K, T> Map<K, T>::operator=(const Map &&m) {
  Tree<K, T>::operator=(std::move(m));
  return *this;
}

template <typename K, typename T>
inline T &Map<K, T>::at(const key_type &key) {
  return Tree<K, T>::at(key);
}

template <typename K, typename T>
inline T &Map<K, T>::operator[](const key_type &key) {
  return Tree<K, T>::operator[](key);
}

template <typename K, typename T>
inline typename Map<K, T>::iterator Map<K, T>::begin() {
  return Tree<K, T>::begin();
}

template <typename K, typename T>
inline typename Map<K, T>::iterator Map<K, T>::end() {
  return Tree<K, T>::end();
}

template <typename K, typename T>
inline bool Map<K, T>::empty() const {
  return Tree<K, T>::size() == 0;
}

template <typename K, typename T>
inline typename Map<K, T>::size_type Map<K, T>::size() const {
  return Tree<K, T>::size();
}

template <typename K, typename T>
inline typename Map<K, T>::size_type Map<K, T>::max_size() const {
  return Tree<K, T>::max_size();
}

template <typename K, typename T>
inline void Map<K, T>::clear() {
  Tree<K, T>::clear();
}

template <typename K, typename T>
inline std::pair<typename Map<K, T>::iterator, bool> Map<K, T>::insert(
    const value_type &value) {
  if (Tree<K, T>::contains(value.first)) {
    iterator pos = Tree<K, T>::find_pos_(value.first);

    return std::pair<iterator, bool>(pos, false);
  }
  Tree<K, T>::push_(value.first, value.second);
  iterator pos = Tree<K, T>::find_pos_(value.first);

  return std::pair<iterator, bool>(pos, true);
}

template <typename K, typename T>
inline std::pair<typename Map<K, T>::iterator, bool> Map<K, T>::insert(
    const key_type &key, const T &obj) {
  if (Tree<K, T>::contains(key)) {
    iterator pos = Tree<K, T>::find_pos_(key);

    return std::pair<iterator, bool>(pos, false);
  }
  Tree<K, T>::push_(key, obj);
  iterator pos = Tree<K, T>::find_pos_(key);

  return std::pair<iterator, bool>(pos, true);
}

template <typename K, typename T>
inline std::pair<typename Map<K, T>::iterator, bool>
Map<K, T>::insert_or_assign(const key_type &key, const T &obj) {
  if (Tree<K, T>::contains(key)) {
    iterator pos = Tree<K, T>::find_pos_(key);
    pos->second = obj;

    return std::pair<iterator, bool>(pos, false);
  }
  Tree<K, T>::push_(key, obj);
  iterator pos = Tree<K, T>::find_pos_(key);

  return std::pair<iterator, bool>(pos, true);
}

template <typename K, typename T>
inline void Map<K, T>::erase(iterator pos) {
  Tree<K, T>::erase(pos);
}

template <typename K, typename T>
inline void Map<K, T>::swap(Map &other) {
  Tree<K, T>::swap(other);
}

template <typename K, typename T>
inline void Map<K, T>::merge(Map &other) {
  Tree<K, T>::merge(other);
}

template <typename K, typename T>
inline bool Map<K, T>::contains(const key_type &key) const {
  return Tree<K, T>::contains(key);
}

template <typename key_type, typename mapped_type>
template <class... Args>
Vector<std::pair<typename Map<key_type, mapped_type>::iterator, bool>>
Map<key_type, mapped_type>::insert_many(Args &&...args) {
  Vector<std::pair<typename Tree<key_type, mapped_type>::iterator, bool>> ret;
  for (auto arg : {args...}) {
    if (contains(arg.first)) {
      ret.push_back(
          std::pair(Tree<key_type, mapped_type>::find_pos_(arg.first), false));
    } else {
      Tree<key_type, mapped_type>::push_(arg.first, arg.second);
      ret.push_back(
          std::pair(Tree<key_type, mapped_type>::find_pos_(arg.first), true));
    }
  }
  return ret;
}

}  // namespace s21

#endif