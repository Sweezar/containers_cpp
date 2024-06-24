#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <iostream>

namespace s21 {
#define MAX_LIST_SIZE 768614336404564650

template <class T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

 private:
  struct Node {
    Node(value_type data) noexcept : data(data){};
    const_reference &GetData() { return data; };
    value_type data;
    Node *next = nullptr;
    Node *prev = nullptr;
  };

  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  size_type size_ = 0;
  size_type max_size_ = MAX_LIST_SIZE;

 public:
  class ListIterator {
   private:
    using Node = typename List<T>::Node;
    Node *cur_ = nullptr;

   public:
    ListIterator(Node *first) : cur_(first){};

    ListIterator operator++(int);  // n++
    ListIterator operator--(int);
    ListIterator &operator++();  //++n
    ListIterator &operator--();

    bool operator!=(const ListIterator &it);
    bool operator==(const ListIterator &it);

    Node *get();
    reference operator*();
  };

  class ListConstIterator : public ListIterator {
   public:
    ListConstIterator();
    ListConstIterator(const ListIterator &node_);
    const_reference operator*() const;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();

  List &operator=(List &l);

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List &other);
  void merge(List &other);
  void splice(const_iterator pos, List &other);
  void reverse();
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <class... Args>
  void insert_many_back(Args &&...args);
  template <class... Args>
  void insert_many_front(Args &&...args);
};

template <class T>
inline List<T>::List(){};

template <class T>
List<T>::List(size_type n) : max_size_(n) {}

template <class T>
List<T>::List(std::initializer_list<value_type> const &items) : size_(0) {
  for (auto item : items) {
    this->push_back(item);
  }
}

template <class T>
List<T>::List(const List &l) {
  if (l.head_) {
    Node *cur = l.head_;
    while (cur != nullptr) {
      this->push_back(cur->data);
      cur = cur->next;
    }
  }
}

template <class T>
List<T>::List(List &&l) {
  this->size_ = l.size();
  this->max_size_ = l.max_size();
  this->head_ = l.head_;
  this->tail_ = l.tail_;

  l.size_ = 0;
  l.max_size_ = 0;
  l.head_ = nullptr;
  l.tail_ = nullptr;
}

template <class T>
inline List<T>::~List() {
  clear();
}

template <class T>
List<T> &List<T>::operator=(List<T> &l) {
  this->clear();
  for (auto it = l.begin(); it != l.end(); it++) {
    this->push_back(*it);
  }

  return *this;
}

template <class T>
typename List<T>::const_reference List<T>::front() {
  static const T default_value = T{};
  if (this->head_ == nullptr) {
    return default_value;
  } else {
    return this->head_->GetData();
  }
}

template <class T>
typename List<T>::const_reference List<T>::back() {
  static const T default_value = T{};
  if (this->tail_ == nullptr) {
    return default_value;
  } else {
    return this->tail_->GetData();
  }
}

template <class T>
typename List<T>::iterator List<T>::begin() {
  return iterator(head_);
}

template <class T>
typename List<T>::iterator List<T>::end() {
  return iterator(nullptr);
}

template <class T>
bool List<T>::empty() {
  return this->size_ == 0;
}

template <class T>
typename List<T>::size_type List<T>::size() {
  return this->size_;
}

template <class T>
typename List<T>::size_type List<T>::max_size() {
  return this->max_size_;
}

template <class T>
inline void List<T>::clear() noexcept {
  this->size_ = 0;

  while (head_) {
    delete std::exchange(head_, head_->next);
  }

  head_ = nullptr;
  tail_ = nullptr;
}

template <class T>
typename List<T>::iterator List<T>::insert(iterator pos,
                                           const_reference value) {
  Node *cur = pos.get();

  if (cur) {
    if (cur->prev == nullptr) {
      this->push_front(value);
      pos = ListIterator(head_);
    } else {
      Node *newNode = new Node(value);
      newNode->next = cur;
      newNode->prev = cur->prev;
      cur->prev->next = newNode;
      cur->prev = newNode;
      this->size_++;
    }
    --pos;
  } else {
    this->push_back(value);
    pos = ListIterator(head_);
  }

  return pos;
}

template <class T>
void List<T>::erase(iterator pos) {
  Node *cur = pos.get();

  if (cur) {
    if (cur->prev != nullptr) {
      cur->prev->next = cur->next;
    } else {
      head_ = cur->next;
    }

    if (cur->next != nullptr) {
      cur->next->prev = cur->prev;
    } else {
      tail_ = cur->prev;
    }

    delete cur;
    --size_;
  }
}

template <class T>
void List<T>::push_back(const_reference value) {
  auto newnode = new Node(value);

  if (tail_) {
    tail_->next = newnode;
    newnode->prev = tail_;
    tail_ = newnode;
  } else {
    head_ = tail_ = newnode;
  }

  this->size_++;
}

template <class T>
void List<T>::pop_back() {
  if (tail_) {
    Node *node = tail_;
    tail_ = tail_->prev;
    if (tail_) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }

    delete node;
    --size_;
  }
}

template <class T>
void List<T>::push_front(const_reference value) {
  auto newnode = new Node(value);

  if (head_) {
    head_->prev = newnode;
    newnode->next = head_;
    head_ = newnode;
  } else {
    head_ = tail_ = newnode;
  }

  this->size_++;
}

template <class T>
void List<T>::pop_front() {
  if (head_) {
    Node *node = head_;
    head_ = head_->next;
    if (head_) {
      head_->prev = nullptr;
    } else {
      tail_ = nullptr;
    }

    delete node;
    --size_;
  }
}

template <class T>
void List<T>::swap(List &other) {
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->size_, other.size_);
  std::swap(this->max_size_, other.max_size_);
}

template <class T>
void List<T>::merge(List &other) {
  if (other.empty()) {
    return;
  }
  if (this->empty()) {
    this->swap(other);
    return;
  }

  iterator it_this = this->begin();
  iterator it_other = other.begin();

  while (it_other != nullptr) {
    if (it_this == nullptr) {
      Node *tmp = it_other.get();
      it_other = other.end();

      tmp->prev = this->tail_;
      this->tail_->next = tmp;
      this->tail_ = other.tail_;
    } else if (it_this.get()->data > it_other.get()->data) {
      Node *tmp = it_other.get();
      ++it_other;

      tmp->prev = it_this.get()->prev;
      tmp->next = it_this.get();
      if (it_this.get()->prev) {
        it_this.get()->prev->next = tmp;
      }
      it_this.get()->prev = tmp;

      if (tmp->prev == nullptr) {
        this->head_ = tmp;
      }
    } else {
      ++it_this;
    }
  }

  this->size_ += other.size_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.clear();
}

template <class T>
void List<T>::splice(const_iterator pos, List &other) {
  Node *cur = pos.get();

  if (this->empty()) {
    this->head_ = other.head_;
    this->tail_ = other.tail_;
  } else {
    if (cur) {
      if (cur->prev) {
        cur->prev->next = other.head_;
        other.head_->prev = cur->prev;
        cur->prev = other.tail_;
        other.tail_->next = cur;
      } else {
        other.tail_->next = cur;
        this->head_ = other.head_;
      }
    } else {
      other.head_->prev = this->tail_;
      this->tail_->next = other.head_;
      this->tail_ = other.tail_;
    }
  }

  this->size_ += other.size_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
}

template <class T>
void List<T>::reverse() {
  std::swap(head_, tail_);
  for (iterator it = this->begin(); it != this->end(); ++it) {
    std::swap(it.get()->next, it.get()->prev);
  }
}

template <class T>
void List<T>::unique() {
  for (iterator it = this->begin(); it != this->end(); ++it) {
    if (it.get()->prev && *it == it.get()->prev->data) {
      iterator tmp_it = it;
      this->erase(--tmp_it);
    }
  }
}

template <class T>
void List<T>::sort() {
  if (size() < 2) {
    return;
  }

  List<T> left, right;
  size_t middle = size() / 2;
  iterator it = begin();

  for (size_t i = 0; i < middle; ++i) {
    left.push_back(*it);
    ++it;
  }

  for (size_t i = middle; i < size(); ++i) {
    right.push_back(*it);
    ++it;
  }

  left.sort();
  right.sort();

  clear();

  left.merge(right);
  this->merge(left);
}

template <class T>
template <class... Args>
typename List<T>::iterator List<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  (insert(pos, args), ...);
  return pos;
}

template <class T>
template <class... Args>
void List<T>::insert_many_back(Args &&...args) {
  (push_back(args), ...);
}

template <class T>
template <class... Args>
void List<T>::insert_many_front(Args &&...args) {
  iterator it = begin();
  (insert(it, args), ...);
  it = nullptr;  // обнуление нужно для случая, когда в args нет элементов, так
                 // как возникает неиспользуемая переменная
}

template <class T>
typename List<T>::ListIterator List<T>::ListIterator::operator++(int) {
  ListIterator tmp(*this);
  if (cur_ != nullptr) {
    cur_ = cur_->next;
  }

  return tmp;
}

template <class T>
typename List<T>::ListIterator List<T>::ListIterator::operator--(int) {
  ListIterator tmp(*this);
  if (cur_ != nullptr) {
    cur_ = cur_->prev;
  }

  return tmp;
}

template <class T>
typename List<T>::ListIterator &List<T>::ListIterator::operator++() {
  if (cur_ != nullptr) {
    cur_ = cur_->next;
  }
  return *this;
}

template <class T>
typename List<T>::ListIterator &List<T>::ListIterator::operator--() {
  if (cur_ != nullptr) {
    cur_ = cur_->prev;
  }
  return *this;
}

template <class T>
bool List<T>::ListIterator::operator!=(const ListIterator &it) {
  return this->cur_ != it.cur_;
}

template <class T>
bool List<T>::ListIterator::operator==(const ListIterator &it) {
  return this->cur_ == it.cur_;
}

template <class T>
typename List<T>::ListIterator::Node *List<T>::ListIterator::get() {
  return cur_;
}

template <class T>
typename List<T>::reference List<T>::ListIterator::operator*() {
  return cur_->data;
}

template <class T>
List<T>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <class T>
List<T>::ListConstIterator::ListConstIterator(const ListIterator &node_)
    : ListIterator(node_) {}

template <class T>
typename List<T>::const_reference List<T>::ListConstIterator::operator*()
    const {
  return ListIterator::operator*();
}

}  // namespace s21

#endif