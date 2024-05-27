#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {
#define MAX_LIST_SIZE 768614336404564650

template <class T>
class List {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  // using iterator = ListIterator;
  // using const_iterator = ListConstIterator;
  using size_type = std::size_t;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();

  // List& operator=(List &&l);

  const_reference front();
  const_reference back();

  // iterator begin();
  // iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear() noexcept;
  // iterator insert(iterator pos, const_reference value);
  // void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  // void swap(List& other);
  // void merge(List& other);
  // void splice(const_iterator pos, List& other);
  // void reverse();
  // void unique();
  // void sort();

 private:
  struct Node
  {
        Node(value_type data) noexcept
            : data(data) {};
        const_reference& GetData() {return data;};
        value_type data;
        Node* next = nullptr;
        Node* prev = nullptr;
  };

  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_type size_;
  size_type max_size_ = MAX_LIST_SIZE;

  // class ListIterator
  // {
  //     public:
  //         ListIterator(Node* first);

  //         iterator& operator++(int); // n++
  //         iterator& operator--(int);
  //         iteratorT& operator++(); //++n
  //         iterator& operator--();

  //         bool operator!=(const_iterator& it);
  //         bool operator==(const_iterator& it);

  //         value_type* operator->();
  //         value_type operator*();

  //     private:
  //         Node<value_type>* cur_;
  // };

  // class ListConstIterator
  // {
  //     public:

  //     private:

  // };
};
}  // namespace s21

#include "list.cc"

#endif