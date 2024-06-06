#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cassert>
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

  class ListIterator
  {
      private:
          using Node = typename List<T>::Node;
          Node* cur_ = nullptr;

      public:
          ListIterator(Node* first) : cur_(first) {};

          ListIterator operator++(int); // n++
          ListIterator operator--(int);
          ListIterator& operator++(); //++n
          ListIterator& operator--();

          bool operator!=(const ListIterator& it);
          bool operator==(const ListIterator& it);

          Node* get();
          reference operator*();
  };

  class ListConstIterator : public ListIterator 
  {
   public:
    ListConstIterator();
    ListConstIterator(const ListIterator &node_);
    const_reference operator*() const;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const &items);
  List(const List &l);
  List(List &&l);
  ~List();

  List& operator=(List &&l);

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
  void swap(List& other);
  void merge(List& other);
  void splice(const_iterator pos, List& other);
  // void reverse();
  // void unique();
  void sort();


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
  size_type size_ = 0;
  size_type max_size_ = MAX_LIST_SIZE;

  void merge_sort(Node** head_ref);
  void split_list(Node* source, Node** left, Node** right);
  Node* sorted_merge(Node* first, Node* second);

};

} // namespace s21

#include "list.cc"

#endif