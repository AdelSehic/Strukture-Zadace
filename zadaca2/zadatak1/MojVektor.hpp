#pragma once

#include <algorithm>
#include <iterator>
#include <iostream>
#include <stdexcept>

template <typename T> 
class MojVector {
public:
  MojVector() : capacity_{1}, arr_{new T[capacity_]}, size_{0} {} ;
  MojVector(const std::initializer_list<T> &a) 
  : capacity_{a.size()}, size_{capacity_}, arr_{new T[size_]} {
    // auto it = a.begin();
    // for( int i = 0; it!=a.end(); ++i){
    //   arr_[i] = *it;
    //   ++it;
    // }
    std::copy( a.begin(), a.end(), arr_ );
  };

  MojVector(const MojVector &other)
  : capacity_{other.capacity_}, size_{other.size_}, arr_{new T[size_]} {
    for (size_t i = 0; i < size_; ++i)
      arr_[i] = other.arr_[i];
  }

  MojVector &operator=(const MojVector & other) {
    delete[] arr_;

    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = new T[capacity_];

    for (size_t i = 0u; i < size_; i++) {
      arr_[i] = other.arr_[i];
    }

    return *this;
  }

  MojVector(MojVector && other)
  : capacity_{other.capacity_}, size_{other.size_}, arr_{other.arr_} {
    other.arr_ = nullptr;
    other.capacity_ = other.size_ = 0;
  }

  MojVector &operator=(MojVector && other) {
    if (this == &other) return *this;

    delete[] arr_;
  
    capacity_ = other.capacity_;
    size_ = other.size_;
    arr_ = other.arr_;
  
    other.arr_ = nullptr;
    other.capacity_ = other.size_ = 0;
  
    return *this;
  }

  ~MojVector() { delete [] arr_; };

  // MojVector &push_back(T);

  void push_back(const T& element) {
    if (size_ == capacity_) {
      reallocate();
    }
    arr_[size_++] = element;
  }

  T& at(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Indeksiranje izvan granica");
    }
    return arr_[index];
  }
  const T& at(size_t index) const {
    if (index >= size_) {
      throw std::out_of_range("Indeksiranje izvan granica");
    }
    return arr_[index];
  }

  T& operator[](size_t index) { return arr_[index]; }
  const T& operator[](size_t index) const { return arr_[index]; }

  void clear() { 
    size_ = 0;
    auto it = begin();
    while( it != end() ){
      auto temp = std::move(it);
      ++it;
    }
  };

  size_t size() const { return size_; }
  bool empty() const { return size_ == 0; }
  T& front() {return arr_[0];}
  const T& front() const {return arr_[0];  }
  T& back() {return arr_[size_-1];}
  const T& back() const {return arr_[size_-1];}

  // void resize(size_t a){
  //   while( capacity_ < a ) reallocate();
  //   size_ = a;
  // }

  void resize( size_t br ) {
    size_t tmpSize = ( size_ > br ) ? br : size_;
    T* temp = new T[br];
    for ( auto i = 0u; i < tmpSize; ++i ){
      temp[i] = arr_[i];
    }
    for(auto i = tmpSize; i < br; ++i){
      temp[i] = 0;
    }
    delete [] arr_;
    arr_ = temp;
    size_ = br;
    capacity_ = br*2;
  }

  MojVector &pop_back(){
    auto temp = std::move(arr_[size_]);
    if(size_) --size_;
    return *this;
  }

  size_t capacity() const { return capacity_; }
  bool operator==(const MojVector &other) const{
    if( size_ != other.size_ ) return false;
    for (size_t i = 0; i < size_; ++i)
      if( arr_[i] != other.arr_[i] ) return false;
    return true;
    // if( std::equal( begin(), end(), other.begin() ) ) return true;
    // return false;
  }
  bool operator!=(const MojVector &other) const {
    return !(*this==other);
  }

  class Iterator;
  Iterator begin() { return Iterator{arr_}; }
  Iterator end() { return Iterator{arr_ + size_}; }
  Iterator begin() const { return Iterator{arr_}; }
  Iterator end() const { return Iterator{arr_ + size_}; }
  Iterator find(const T &element) const {
    auto it = begin();
    while( *it != element ) ++it;
    return it;
  }
  MojVector& insert(Iterator inset, T element){
    if(inset == end()) {
      push_back(element);
      return *this;
    }
    if(size_==capacity_) {
      auto temp = end() - inset;
      reallocate();
      inset = end() - temp;
    }
    auto it = end();
    while( it != inset ){
      *it = *(it-1);
      --it;
    }
    *it = element;
    ++size_;
    return *this;
  }
  Iterator erase(Iterator pos) {
    erase(pos, pos+1);
    return pos;
  //   if(pos == end()) pop_back();
  //   auto temp = pos;
  //   for( auto it = pos+1; it < end(); ++it, ++temp ){
  //   *temp = *it;
  //   }
  //   --size_;
  //   return pos;
  }
  // Iterator erase(Iterator pos) {
  //   std::cout << "ide\n";
  //   auto temp = pos+1;
  //   while( temp != end() );{
  //     *pos = *temp;
  //     ++pos;
  //     ++temp;
  //     std::cout << "ide\n";
  //   }
  //   --size_;
  //   return pos;
  // }
  Iterator erase(Iterator beginIt, Iterator endIt){
    auto temp = beginIt+1;
    if(endIt!=end()){
      while( endIt != end() ){
        *beginIt = *endIt;
        ++endIt;
        ++beginIt;
      }
    }
    size_-= endIt-beginIt;
    return temp;
  }

private:

void reallocate(){
  capacity_*=2;
  auto temp = new T[capacity_];
  std::move(begin(), end(), temp);
  std::swap( arr_, temp);
  delete [] temp;
}

  size_t capacity_ = 10;
  size_t size_ = 0;
  T *arr_ = new T[capacity_];
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVector<T> &vek){
  for(int i = 0; i < vek.size(); ++i)
    std::cout << vek.at(i) << ' ';
  std::cout << std::endl;
  return out;
}

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr) : ptr_{ptr} {};
  T& operator*() { return *ptr_; }
  T* operator->() { return ptr_; }
  Iterator& operator++() {
    ++ptr_;
    return *this;
  }
  Iterator operator++(int) {
    auto temp = *this;
    ++ptr_;
    return temp;
  }
  Iterator& operator--() {
    --ptr_;
    return *this;
  }
  Iterator operator--(int) { 
    auto temp = *this;
    --ptr_;
    return temp;
  }
  Iterator operator+(int index) {
    return ptr_+index;
  }
  Iterator operator-(int index) {
    return ptr_-index;
  }
  size_t operator-(const Iterator& other) { 
    return ptr_ - other.ptr_;
  }

  bool operator==(const Iterator& other) {
    return ptr_ == other.ptr_;
  }
  bool operator!=(const Iterator& other) { 
    return ptr_ != other.ptr_;
  }
  bool operator<(const Iterator& other) {
    return *ptr_ < *other.ptr_;
  }

  ~Iterator(){};

private:
  T *ptr_;
};
