#include "list.h"
#include <iostream>

namespace s21 {

template <class T>
inline List<T>::List() : size_(0) {};

template <class T>
List<T>::List(size_type n) : size_(0), max_size_(n){}

template <class T>
List<T>::List(std::initializer_list<value_type> const &items)
{
    this->size_ = items.size();
    // this->max_size_ = items.max_size();
  // WIP
}

template <class T>
List<T>::List(const List &l)
{
    this->size_ = l.size();
    this->max_size_ = l.max_size();
    this.head_ = l.front();
    this.tail_ = l.back();
}

template <class T>
List<T>::List(List &&l)
{
    this->size_ = l.size();
    this->max_size_ = l.max_size();
    this.head_ = l.front();
    this.tail_ = l.back();

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
typename List<T>::const_reference List<T>::front()
{
    static const T default_value = T{};
    if (this->head_ == nullptr) {
        return default_value;
    } else {
        return this->head_->GetData();
    }
}

template <class T>
typename List<T>::const_reference List<T>::back()
{
    static const T default_value = T{};
    if (this->tail_ == nullptr) {
        return default_value;
    } else {
        return this->tail_->GetData();
    }
}

template <class T>
bool List<T>::empty()
{
    return this->size_ == 0;
}

template <class T>
typename List<T>::size_type List<T>::size()
{
    return this->size_;
}

template <class T>
typename List<T>::size_type List<T>::max_size()
{
    return this->max_size_;
}
template <class T>
inline void List<T>::clear() noexcept
{
    this->size_ = 0;
    
    while (head_)
    {
      delete std::exchange(head_, head_->next);
    }

    tail_ = nullptr;
  
}

template <class T>
void List<T>::push_back(const_reference value)
{
    auto newnode = new Node(value);

    if(tail_) {
        tail_->next = newnode;
        newnode->prev = tail_;
        tail_ = newnode;     
    } else {
        head_ = tail_ = newnode;
    }

    this->size_++;
}

template <class T>
void List<T>::pop_back()
{
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
void List<T>::push_front(const_reference value)
{
    auto newnode = new Node(value);

    if(head_) {
        head_->prev = newnode;
        newnode->next = head_;
        head_ = newnode;     
    } else {
        head_ = tail_ = newnode;
    }

    this->size_++;
}

template <class T>
void List<T>::pop_front()
{
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

}  // namespace s21