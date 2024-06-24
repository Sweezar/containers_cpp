#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>
#include "../list/list.h"

namespace s21 {

template <class T>
class Queue : private List<T> {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  Queue();
  Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& q);
  Queue(Queue&& q);
  ~Queue();

  Queue<T>& operator=(Queue& q);

  const_reference front();
  const_reference back();

  bool empty();
  size_type size();

  void push(const_reference value);
  void pop();
  void swap(Queue& other);

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  struct Node {
    Node(value_type data) noexcept : data(data){};
    const_reference& GetData() { return data; };
    value_type data;
    Node* next = nullptr;
    Node* prev = nullptr;
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_type size_ = 0;
};

template <class T>
inline Queue<T>::Queue() : List<T>() {}

template <class T>
Queue<T>::Queue(std::initializer_list<value_type> const& items)
    : List<T>(items) {}

template <class T>
Queue<T>::Queue(const Queue& q) : List<T>(q) {}

template <class T>
Queue<T>::Queue(Queue&& q) : List<T>(std::move(q)) {}

template <class T>
Queue<T>::~Queue() {}

template <class T>
Queue<T>& Queue<T>::operator=(Queue& q) {
  this->clear();
  Queue tmp(q);
  this->swap(tmp);

  return *this;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::front() {
  return this->List<T>::front();
}

template <class T>
typename Queue<T>::const_reference Queue<T>::back() {
  return this->List<T>::back();
}

template <class T>
bool Queue<T>::empty() {
  return this->List<T>::empty();
}

template <class T>
typename Queue<T>::size_type Queue<T>::size() {
  return this->List<T>::size();
}

template <class T>
void Queue<T>::push(const_reference value) {
  this->List<T>::push_back(value);
}

template <class T>
void Queue<T>::pop() {
  this->List<T>::pop_front();
}

template <class T>
void Queue<T>::swap(Queue& other) {
  this->List<T>::swap(other);
}

template <class T>
template <class... Args>
inline void Queue<T>::insert_many_back(Args&&... args) {
  this->List<T>::insert_many_back(args...);
}

}  // namespace s21

#endif