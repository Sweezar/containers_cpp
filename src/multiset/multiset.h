#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include "../set/set.h"

namespace s21 {

template <typename Key>
class Multiset : public Set<Key> {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Tree<key_type, value_type>::iterator;

  using size_type = std::size_t;

  Multiset();
  Multiset(std::initializer_list<value_type> const &items);
  Multiset(const Multiset &ms);
  Multiset(Multiset &&ms);
  ~Multiset() = default;
  Multiset &operator=(Multiset &&ms);

  iterator begin();
  iterator end();

  bool empty();          // checks whether the container is empty
  size_type size();      // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements

  void clear();  // clears the contents
  iterator insert(
      const value_type &value);  // inserts node and returns iterator to where
                                 // the element is in the container
  void erase(iterator pos);      // erases element at pos
  void swap(Multiset &other);    // swaps the contents
  void merge(Multiset &other);   // splices nodes from another container

  size_type count(
      const Key &key);  // returns the number of elements matching specific key
  iterator find(const Key &key);  // finds element with specific key
  bool contains(const Key &key);  // checks if the container contains element
                                  // with specific key
  std::pair<iterator, iterator> equal_range(
      const Key &key);  // returns range of elements matching a specific key
  iterator lower_bound(const Key &key);  // returns an iterator to the first
                                         // element not less than the given key
  iterator upper_bound(const Key &key);  // returns an iterator to the first
                                         // element greater than the given key

  template <class... Args>
  Vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename T>
Multiset<T>::Multiset() : Set<T>() {
  Set<T>::is_multi_set = true;
}

template <typename Key>
inline Multiset<Key>::Multiset(std::initializer_list<value_type> const &items)
    : Set<Key>() {
  Set<Key>::is_multi_set = true;
  for (auto &item : items) {
    Set<Key>::insert(item);
  }
}

template <typename Key>
inline Multiset<Key>::Multiset(const Multiset &ms) : Set<Key>(ms) {
  Set<Key>::is_multi_set = true;
}

template <typename Key>
inline Multiset<Key>::Multiset(Multiset &&ms) : Set<Key>(std::move(ms)) {
  Set<Key>::is_multi_set = true;
}

template <typename Key>
inline Multiset<Key> &Multiset<Key>::operator=(Multiset &&ms) {
  Set<Key>::operator=(std::move(ms));
  return *this;
}

template <typename Key>
inline typename Multiset<Key>::iterator Multiset<Key>::begin() {
  return Set<Key>::begin();
}

template <typename Key>
inline typename Multiset<Key>::iterator Multiset<Key>::end() {
  return Set<Key>::end();
}

template <typename Key>
inline bool Multiset<Key>::empty() {
  return Set<Key>::empty();
}

template <typename Key>
inline typename Multiset<Key>::size_type Multiset<Key>::size() {
  return Set<Key>::size();
}

template <typename Key>
inline typename Multiset<Key>::size_type Multiset<Key>::max_size() {
  return Set<Key>::max_size();
}

template <typename Key>
inline void Multiset<Key>::clear() {
  Set<Key>::clear();
}

template <typename Key>
inline typename Multiset<Key>::iterator Multiset<Key>::insert(
    const value_type &value) {
  return Set<Key>::insert(value).first;
}

template <typename Key>
inline void Multiset<Key>::erase(iterator pos) {
  Set<Key>::erase(pos);
}

template <typename Key>
inline void Multiset<Key>::swap(Multiset &other) {
  Set<Key>::swap(other);
}

template <typename Key>
inline void Multiset<Key>::merge(Multiset &other) {
  Set<Key>::merge(other);
}

template <typename Key>
inline typename Multiset<Key>::size_type Multiset<Key>::count(const Key &key) {
  size_type count = 0;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      count++;
    }
  }
  return count;
}

template <typename Key>
inline typename Multiset<Key>::iterator Multiset<Key>::find(const Key &key) {
  return Set<Key>::find(key);
}

template <typename Key>
inline bool Multiset<Key>::contains(const Key &key) {
  return Set<Key>::contains(key);
}

template <typename Key>
inline std::pair<typename Multiset<Key>::iterator,
                 typename Multiset<Key>::iterator>
Multiset<Key>::equal_range(const Key &key) {
  iterator it_first = end();
  iterator it_second = end();
  bool found = false;
  for (auto it = begin(); it != end(); ++it) {
    if (*it == key) {
      if (!found) {
        it_first = it;
        found = true;
      }
      it_second = it;
    }
  }

  return std::pair<typename Multiset<Key>::iterator,
                   typename Multiset<Key>::iterator>(it_first, it_second);
}

template <typename Key>
inline typename Multiset<Key>::iterator Multiset<Key>::lower_bound(
    const Key &key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it >= key) return it;
  }
  return end();
}

template <typename Key>
inline typename Multiset<Key>::iterator Multiset<Key>::upper_bound(
    const Key &key) {
  for (auto it = begin(); it != end(); ++it) {
    if (*it > key) return it;
  }
  return end();
}

template <typename Key>
template <class... Args>
inline Vector<std::pair<typename Multiset<Key>::iterator, bool>>
Multiset<Key>::insert_many(Args &&...args) {
  return Set<Key>::insert_many(std::forward<Args>(args)...);
}

}  // namespace s21

#endif