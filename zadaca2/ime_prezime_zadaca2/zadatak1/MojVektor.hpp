#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T> 
class MojVector {
public:
  MojVector();
  MojVector(const std::initializer_list<T> &);
  MojVector(const MojVector &);
  MojVector &operator=(const MojVector &);
  MojVector(MojVector &&);
  MojVector &operator=(MojVector &&);
  ~MojVector();

  MojVector &push_back(T);
  T &at(size_t) const;
  T &operator[](size_t) const;
  void clear();

  size_t size() const;
  bool empty() const;
  const T &back() const;
  const T &front() const;
  T &back(){};
  T &front(){};

  void resize(size_t);

  MojVector &pop_back();
  size_t capacity() const;
  bool operator==(const MojVector &) const;
  bool operator!=(const MojVector &) const;

  class Iterator;
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T &element) const;
  MojVector &insert(Iterator, T element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);

private:
  size_t capacity_;
  size_t size_;
  T *arr_;
};

template <typename T>
std::ostream &operator<<(std::ostream &, const MojVector<T> &);

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr);
  T &operator*() const;
  T *operator->() const;
  Iterator &operator++();
  Iterator operator++(int);
  Iterator &operator--();
  Iterator operator--(int);
  Iterator operator+(size_t index);
  Iterator operator-(size_t index){};
  size_t operator-(Iterator other){};

  bool operator==(const Iterator &it) const;
  bool operator!=(const Iterator &it) const;
  bool operator<(const Iterator &it) const {};

  ~Iterator();

private:
  T *ptr_;
};
