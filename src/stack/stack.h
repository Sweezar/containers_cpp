#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>
#include "../list/list.h"

namespace s21 {

template <class T>
class Stack : private List<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() : List<T>() {}

  Stack(std::initializer_list<value_type> const &items) : List<T>(items) {}

  Stack(const Stack &q) : List<T>(q) {}

  Stack(Stack &&q) : List<T>(std::move(q)) {}

  ~Stack() {}

  Stack<T> &operator=(Stack &q) {
    this->clear();
    Stack tmp(q);
    this->swap(tmp);

    return *this;
  }

  const_reference top() { return List<T>::back(); }

  bool empty() { return this->List<T>::empty(); }

  size_type size() { return this->List<T>::size(); }

  void push(const_reference value) { this->List<T>::push_back(value); }

  void pop() { this->List<T>::pop_back(); }

  void swap(Stack &other) { this->List<T>::swap(other); }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    this->List<T>::insert_many_front(args...);
  }

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
};
}  // namespace s21
#endif