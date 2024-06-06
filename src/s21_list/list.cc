#include "list.h"

namespace s21 {

template <class T>
inline List<T>::List() {};

template <class T>
List<T>::List(size_type n) : max_size_(n){}

template <class T>
List<T>::List(std::initializer_list<value_type> const &items) : size_(0)
{
    for (auto item : items)
    {
        this->push_back(item);
    }
    
}

template <class T>
List<T>::List(const List &l)
{
    if(l.head_) {
        Node *cur = l.head_;
        while(cur != nullptr) {
            this->push_back(cur->data);
            cur = cur->next;
        }
    }
}

template <class T>
List<T>::List(List &&l)
{
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
List<T> &List<T>::operator=(List<T> &&l)
{
    for(auto it = l->begin(); it != l->end(); it++) {
        this->push_back(it);
    }
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
typename List<T>::iterator List<T>::begin()
{
    return iterator(head_);
}

template <class T>
typename List<T>::iterator List<T>::end()
{
    return iterator(nullptr);
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
typename List<T>::iterator List<T>::insert(iterator pos, const_reference value)
{
    Node* cur = pos.get();   
	
    if(cur) 
    {
        if (cur->prev == nullptr)
        {
            this->push_front(value);
            pos = ListIterator(head_);
        }
        else
        {
            Node* newNode = new Node(value);
            newNode->next = cur;
            newNode->prev = cur->prev;
            cur->prev->next = newNode;
            cur->prev = newNode;
            this->size_++;
        }
        --pos;
    }
    else
    {
        this->push_back(value);
        pos = ListIterator(head_);
    }

	return pos;
}

template <class T>
void List<T>::erase(iterator pos)
{
    Node* cur = pos.get();   

    if(cur)
    {
        if(cur->prev != nullptr)
        {
            cur->prev->next = cur->next;
        }
        else
        {
            head_ = cur->next;
        }

        if(cur->next != nullptr)
        {
            cur->next->prev = cur->prev;
        }
        else
        {
            tail_ = cur->prev;
        }

        delete cur;
        --size_;
    }
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

template <class T>
void List<T>::swap(List &other)
{
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->size_, other.size_);
    std::swap(this->max_size_, other.max_size_);
}

template <class T>
void List<T>::merge(List &other)
{
    // this = sorted_merge(this, other);
}

template <class T>
void List<T>::splice(const_iterator pos, List &other)
{
    Node* cur = pos.get();   
    
    if(this->empty()) {
        this->head_ = other.head_;
        this->tail_ = other.tail_;
    } 
    else
    {
        if(cur) {
            if(cur->prev)
            {
                cur->prev->next = other.head_;
                other.head_->prev = cur->prev;
                cur->prev = other.tail_;
                other.tail_->next = cur;
            }
            else
            {
                other.tail_->next = cur;
                this->head_ = other.head_;
            }
        }
        else
        {
            other.head_->prev = this->tail_;
            this->tail_->next = other.head_;
            this->tail_ = other.tail_;
        }
    }

    this->size_+= other.size_; 
    other.size_ = 0;
    other.head_ = nullptr;
    other.tail_ = nullptr;
}

template <class T>
void List<T>::sort()
{
    this->merge_sort(&head_);
}

template <class T>
void List<T>::merge_sort(Node **head_ref)
{
    Node* head = *head_ref;
    Node* first;
    Node* second;

    if(head == nullptr || head->next == nullptr) 
    {
        return;
    }

    split_list(head, &first, &second);
    merge_sort(&first);
    merge_sort(&second);

    *head_ref = sorted_merge(first, second);
}

template <class T>
void List<T>::split_list(Node *source, Node **left, Node **right)
{
    Node* slow = source;
    Node* fast = source->next;

    while(fast) 
    {
        fast = fast->next;
        if(fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *left = source;
    slow->next->prev = nullptr;
    *right = slow->next;
    slow->next = nullptr;
    
}

template <class T>
typename List<T>::Node* List<T>::sorted_merge(Node *first, Node *second)
{
    Node* result = nullptr;

    if(first == nullptr)
    {
        return second;
    }
    else if(second == nullptr)
    {
        return first;
    }

    if(first->data <= second->data)
    {
        result = first;
        result->next = sorted_merge(first->next, second);
    }
    else
    {
        result = second;
        result->next = sorted_merge(first, second->next);
    }

    return result;
}

template <class T>
typename List<T>::ListIterator List<T>::ListIterator::operator++(int)
{
   ListIterator tmp(*this);
   if(cur_ != nullptr)
   {
    cur_ = cur_->next;
   } 

   return tmp;
}

template <class T>
typename List<T>::ListIterator List<T>::ListIterator::operator--(int)
{
   ListIterator tmp(*this);
   if(cur_ != nullptr)
   {
    cur_ = cur_->prev;
   } 

   return tmp;
}

template <class T>
typename List<T>::ListIterator &List<T>::ListIterator::operator++()
{
   if(cur_ != nullptr)
   {
    cur_ = cur_->next;
   }
    return *this;
}

template <class T>
typename List<T>::ListIterator &List<T>::ListIterator::operator--()
{
    if(cur_ != nullptr)
    {   
        cur_ = cur_->prev;
    }
    return *this;
}

template <class T>
bool List<T>::ListIterator::operator!=(const ListIterator &it)
{
    return this->cur_ != it.cur_;
}

template <class T>
bool List<T>::ListIterator::operator==(const ListIterator &it)
{
    return this->cur_ == it.cur_;
}

template <class T>
typename List<T>::ListIterator::Node* List<T>::ListIterator::get()
{
    return cur_;
}

template <class T>
typename List<T>::reference List<T>::ListIterator::operator*()
{
    return cur_->data;
}

template <class T>
List<T>::ListConstIterator::ListConstIterator() : ListIterator() {}

template <class T>
List<T>::ListConstIterator::ListConstIterator(const ListIterator& node_)
    : ListIterator(node_) {}

template <class T>
typename List<T>::const_reference List<T>::ListConstIterator::operator*() const {
  return ListIterator::operator*();
}

}  // namespace s21