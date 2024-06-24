#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {
#define MAX_VECTOR_SIZE 21

template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using iterator = T *;
  using const_iterator = const T *;

  Vector() : size_(0), capacity_(0), data_(nullptr), alloc_() {}

  Vector(size_type n) : Vector() {
    if (n > this->max_size()) throw std::invalid_argument("Invalid argument");
    this->size_ = n;
    this->capacity_ = n;
    // this->data_ = new value_type[n]{};
    this->data_ = alloc_.allocate(n * sizeof(value_type));
    for (size_type i = 0; i < n; ++i) {
      this->data_[i] = 0; 
    }
  }

  Vector(std::initializer_list<value_type> const &items) : alloc_() {
    this->size_ = items.size();
    this->capacity_ =
        (items.size() < MAX_VECTOR_SIZE) ? MAX_VECTOR_SIZE : items.size();
    // this->data_ = new value_type[capacity_]{};
    this->data_ = alloc_.allocate(capacity_);

    size_type index = 0;
    for (value_type item : items) {
      data_[index++] = item;
    }
  }

  Vector(const Vector &v) : alloc_() {
    this->size_ = v.size_;
    this->capacity_ = v.capacity_;
    // this->data_ = new value_type[v.capacity_];
    this->data_ = alloc_.allocate(v.size());
    for (size_type i = 0; i < this->size_; ++i) {
      this->data_[i] = v.data_[i];
    }
  }

  Vector(Vector &&v) {
    data_ = v.data_;
    size_ = v.size_;
    capacity_ = v.capacity_;
    alloc_ = v.alloc_;
    v.data_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }

  ~Vector() {
    alloc_.deallocate(this->data_, this->capacity_);
    this->size_ = 0;
    this->capacity_ = 0;
    this->data_ = nullptr;
  }

  Vector<T> &operator=(Vector<T> &&v) {
    if (this != &v) {
      this->swap(v);
      // delete[] v.data_;
      v.clear();
    }

    return *this;
  }

  // -===Element access===-
  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);              // access specified element
  const_reference operator[](size_type pos) const;  // access specified element
  const_reference front() const;                    // access the first element
  const_reference back() const;                     // access the last element
  value_type* data();  // direct access to the underlying array

  // -===Iterators===-
  iterator begin() const;  // returns an iterator to the beginning
  iterator end() const;    // returns an iterator to the end

  // -===Capacity===-
  bool empty() const;      // checks whether the container is empty
  size_type size() const;  // returns the number of elements
  size_type max_size()
      const;  // returns the maximum possible number of elementsuff,
  void reserve(
      size_type size);  // allocate storage of size elements and copies
                        // current array elements to a newely allocated array
  size_type capacity() const;  // returns the number of elements that can be
                               // held in currently allocated storage
  void shrink_to_fit();        // reduces memory usage by freeing unused memory

  // -===Modifiers===-
  void clear();  // clears the contents
  iterator insert(
      iterator pos,
      const_reference value);  // inserts elements into concrete pos and returns
                               // the iterator that points to the new element

  void erase(iterator pos);               // erases element at pos
  void push_back(const_reference value);  // adds an element to the end
  void pop_back();                        // removes the last element
  void swap(Vector &other);               // swaps the contents

  // -===Assistans===-

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <class... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type size_;
  size_type capacity_;
  value_type* data_;
  std::allocator<T> alloc_;
};

// -===Element access===-
template <typename T>
T &Vector<T>::at(size_type pos) {
  if (this->size_ <= pos) throw std::out_of_range("Index out of range");
  return data_[pos];
}

template <typename T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  if (pos >= this->size()) throw std::out_of_range("Index is out of range");
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::operator[](size_type pos) const {
  if (pos >= this->size()) throw std::out_of_range("Index is out of range");
  return data_[pos];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::front() const {
  if (this->empty()) throw std::out_of_range("Vector is empty");
  return data_[0];
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::back() const {
  if (this->empty()) throw std::out_of_range("Vector is empty");
  return data_[size_ - 1];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::data() {
  return this->data_;
}

// -===Iterators===-
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
  // if (this->size() == 0)
  //   throw std::invalid_argument("Array is not exist");
  return this->data_;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const {
  // if (this->size() == 0)
  //   throw std::invalid_argument("Array is not exist");

  return this->data_ + size_;
}

// -===Capacity===-
template <typename T>
bool Vector<T>::empty() const {
  // return this->size_ == 0;
  return this->begin() == this->end();
};

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const {
  return std::distance(this->begin(), this->end());
}

template <typename T>
typename Vector<T>::size_type Vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(size_type);
}

template <typename T>
void Vector<T>::reserve(Vector<T>::size_type size) {
  if ((long int)size < 0)
    throw std::length_error("Size can not be less then zero");
  if (size > max_size()) {
    throw std::length_error("Can't allocate memory of this size");
  }
  if (size >= this->capacity()) {
    // T *new_data = new T[size];
    T *new_data = alloc_.allocate(size);

    std::copy(this->begin(), this->end(), new_data);
    alloc_.deallocate(data_, capacity_);
    // delete[] data_;
    data_ = new_data;
    capacity_ = size;
  }
}

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const {
  return this->capacity_;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  // if (this->size_ < this->capacity_) {
  //   T* new_array = new T[this->size_];
  //   std::copy(this->data_, this->data_ + this->size_, new_array);
  //   // delete[] this->data_;
  //   this->alloc_.deallocate(this->data_, this->capacity_);
  //   this->data_ = new_array;
  //   this->capacity_ = this->size_;
  // }

  if (this->size_ < this->capacity_) {
    T* new_array = alloc_.allocate(this->size_);
    std::copy(this->data_, this->data_ + this->size_, new_array);
    for (size_t i = 0; i < this->size_; ++i) {
      alloc_.destroy(&this->data_[i]);
    }
    alloc_.deallocate(this->data_, this->capacity_);
    this->data_ = new_array;
    this->capacity_ = this->size_;
  }
}

// -===Modifiers===-
template <typename T>
void Vector<T>::clear() {
  // if (this->data_ != nullptr) delete[] this->data_;
  if (this->data_ != nullptr) this->alloc_.deallocate(this->data_, this->capacity_);
  this->size_ = 0;
  this->capacity_ = 0;
  this->data_ = nullptr;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos == end()) {
    push_back(value);
    pos = end();
    return --pos;
  }

  size_type diff = pos - begin();

  if (this->size_ >= this->capacity_)
    reserve(this->capacity_ ? this->capacity_ * 2 : 1);

  auto insert_pos = begin() + diff;
  pos = insert_pos;

  T evicted_item = *pos;
  *pos = value;
  pos++;

  for (; pos != end(); ++pos) {
    std::swap(*pos, evicted_item);
  }
  ++size_;
  return insert_pos;
}

template <typename T>
void Vector<T>::push_back(const_reference value) {
  if (this->size_ == this->capacity_)
    reserve(this->capacity_ ? this->capacity_ * 2 : 1);

  this->data_[size_++] = value;
}

template <typename T>
void Vector<T>::erase(iterator pos) {
  if (pos < this->begin() || pos > this->end()) {
    throw std::out_of_range("Erase position is out of range");
  }
  for (iterator it = pos; it != this->end() - 1; ++it) *it = *(it + 1);
  --this->size_;
}

template <typename T>
void Vector<T>::pop_back() {
  if (this->size_ > 0) --this->size_;
}

template <typename T>
void Vector<T>::swap(Vector &other) {
  std::swap(this->data_, other.data_);
  std::swap(this->size_, other.size_);
  std::swap(this->capacity_, other.capacity_);
  std::swap(this->alloc_, other.alloc_);
}
// -===Assistans===-

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  if (pos < this->begin() || pos > this->end())
    throw std::out_of_range("Insert position is out of range");

  Vector<T> tmp{args...};
  iterator current_pos = begin() + (pos - begin());
  for (size_t i = 0; i < tmp.size(); ++i) {
    current_pos = insert(current_pos, tmp[i]);
    ++current_pos;
  }
  return current_pos;
}

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args &&...args) {
  this->insert_many(end(), args...);
}

}  // namespace s21
#endif