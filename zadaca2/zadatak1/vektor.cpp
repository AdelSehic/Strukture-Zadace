#include "MojVektor.hpp"
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <functional>

template < typename T >
MojVector<T>::MojVector() : arr_{new T[1]}, capacity_{1} {}

template < typename T >
MojVector<T>::MojVector( const std::initializer_list<T>& a ) : arr_{new T[size_]}, size_{a.size()}, capacity_{size_} { std::copy(begin(a), end(a), arr_); }

template < typename T >
MojVector<T>::MojVector(const MojVector<T>& a) : arr_{new T[capacity_]}, size_{a.size_}, capacity_{a.capacity_} { 
    kopi(*this, a);
}

template < typename T >
MojVector<T>::MojVector(MojVector&& a) : arr_{a.arr_}, size_{std::move(a.size_)}, capacity_{std::move(a.size_)} { a.arr_ = nullptr; }

/*
template<typename o>

MojVector& operator=(const o& a) {
    delete [] arr_;
    arr_ = new T[a.capacity_];
    size_ = a.size_;
    capacity_ = a.capacity_;
    kopi(*this, a);
    int broj = 0;
    return *this;
}
*/
template < typename T >
MojVector<T>& MojVector<T>::operator=(const MojVector<T>& a) {
    if( this == &a )
        return *this;
    delete [] arr_;
    arr_ = new T[a.capacity_];
    size_ = a.size_;
    capacity_ = a.capacity_;
    kopi(*this, a);
    return *this;
}

template < typename T >
MojVector<T>& MojVector<T>::operator=(MojVector<T>&& a){
    if( this == &a )
        return *this;
    delete [] arr_;
    arr_ = a.arr_;
    size_ = a.size_;
    capacity_ = a.capacity_;
    a.arr_ = nullptr;
    return *this;
}

template < typename T >
MojVector<T>::~MojVector() {delete [] arr_;}

template < typename T >
size_t MojVector<T>::size() const {return size_;}

template < typename T >
bool MojVector<T>::empty() const { return !size_; }

template < typename T >
const T& MojVector<T>::back() const { return *arr_[size_ - 1 ]; }

template < typename T >
const T& MojVector<T>::front() const{ return *arr_[0]; }

template < typename T >
T& MojVector<T>::back(){ return *arr_[size_ - 1 ]; }

template < typename T >
T& MojVector<T>::front(){ return *arr_[0]; }

template < typename T >
void MojVector<T>::resize(size_t kap) {
    while(kap < size_) realloc();
    size_ = kap;
}

template < typename T >
MojVector<T>& MojVector<T>::pop_back(){
    --size_;
}

template < typename T >
size_t MojVector<T>::capacity() const { return capacity_; }

// template < typename T >
// T& MojVector<T>::operator[](size_t a){
//     return at(a);
// }

template < typename T >
T& MojVector<T>::operator[](size_t a) const {
    return at(a);
}

//kopira iz a u b po definisanoj transformaciji :
template<typename c1, typename c2, typename T>
void kopi(c1& b, const c2& a, std::function<T(T)>&& l = [](T a){ return a;}){
    size_t broj = 0;
    while(broj < b.size_ && broj < a.size_){
        b.arr_[broj] = l(a.arr_[broj]);
        ++broj;
    }
}

template < typename T >
MojVector<T>& MojVector<T>::push_back(T a){
    if(size_ == capacity_) reloc();
    arr_[size_] = a;
    ++size_;
    return this;
}

template < typename T >
void MojVector<T>::reloc(){
    MojVector temp{*this};
    capacity_*=2;
    delete [] arr_;
    arr_ = new T[capacity_];
    kopi(*this, temp);
}

template < typename T >
MojVector<T>& MojVector<T>::pop_back() { --this.size_; return this;}

template < typename T >
bool MojVector<T>::operator==(const MojVector &other) const {
    if( size_ != other.size_) return false;
    for (size_t i = 0; i < size_; ++i)
        if( arr_[i] != other.arr_[i] ) return false;
    return true;
}

template < typename T >
bool MojVector<T>::operator!=(const MojVector &other) const{
    return !(*this==other);
}

class Iterator;

template < typename T >
Iterator begin() {
    return Iterator(arr_[0]);
}

template < typename T >
Iterator end() {
    return Iterator(arr_[size_-1]);
}

template < typename T >
Iterator find(const T &element) {
    auto it = begin();
    while( it != end() )
        if( *it == element ) break;
    return it;
}

template < typename T >
MojVector<T>& insert(Iterator ins, T element){
    auto it = end();
    while( it != ins ){
        *it = *(it-1);
        --it;
    }
    *ins = element;
    ++size_;
    return *this;
}

template < typename T >
Iterator erase(Iterator pos){
    for( auto it = pos+1; it < end(); ++it )
    *(it-1) = *it;
    --size_;
    return pos;
}

template < typename T >
Iterator erase(Iterator beginIt, Iterator endIt){
    while( endIt != end() ){
        *beginIt = *endIt;
        ++beginIt;
        ++endIt;
    }
    size_ -= endIt - beginIt;
}

template < typename T >
T& front() { return *arr_[0]; }

template < typename T >
T& back() { return *arr_[size_-1]; }

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr);
  T &operator*() const { return *ptr_; }
  T *operator->() const { return *ptr_; }
  Iterator &operator++() { ++ptr_; return ptr_; }
  Iterator operator++(int) { 
      auto temp = ptr_;
      ++ptr_;
      return temp;
    }
  Iterator &operator--() { --ptr_; return ptr_; }
  Iterator operator--(int){
    auto temp = ptr_;
    --ptr_;
    return temp;
  }
  Iterator operator+(size_t index){ auto temp = ptr_ + index; return temp; }
  Iterator operator-(size_t index){ auto temp = ptr_ - index; return temp; }
  size_t operator-(Iterator other){ return other.ptr_ - ptr_ };

  bool operator==(const Iterator &it) const { return ptr_ == it.ptr_; }
  bool operator!=(const Iterator &it) const { return !(ptr_ == it.ptr_); }
  bool operator<(const Iterator &it) const { return ptr_ < it.ptr_; }

  ~Iterator();

private:
  T *ptr_;
};

/*

#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <functional>

template<typename T>
class MojVector{
    public:
        template<typename Other>
        friend class MojVector;

        MojVector() : arr_{new T[1]}, capacity_{1} {}

        MojVector( std::initializer_list<T> a ) : arr_{new T[size_]}, size_{a.size()}, capacity_{size_} { std::copy(begin(a), end(a), arr_); }

        MojVector(const MojVector<T>& a) : arr_{new T[capacity_]}, size_{a.size_}, capacity_{a.capacity_} { 
            kopi(*this, a);
        }

        MojVector(MojVector&& a) : arr_{a.arr_}, size_{std::move(a.size_)}, capacity_{std::move(a.size_)} { a.arr_ = nullptr; }

        template<typename o>

        MojVector& operator=(const o& a) {
            delete [] arr_;
            arr_ = new T[a.capacity_];
            size_ = a.size_;
            capacity_ = a.capacity_;
            kopi(*this, a);
            int broj = 0;
            return *this;
        }

        MojVector& operator=(const MojVector<T>& a) {
            if( this == &a )
                return *this;
            delete [] arr_;
            arr_ = new T[a.capacity_];
            size_ = a.size_;
            capacity_ = a.capacity_;
            kopi(*this, a);
            return *this;
        }

        MojVector& operator=(MojVector<T>&& a){
            if( this == &a )
                return *this;
            delete [] arr_;
            arr_ = a.arr_;
            size_ = a.size_;
            capacity_ = a.capacity_;
            a.arr_ = nullptr;
            return *this;
        }

        ~MojVector() {delete [] arr_;}
        
        int size() const {return size_;}

        bool empty() const { return !size_; }

        const T &back() const { return *arr_[size_ - 1 ]; }
        const T &front() const{ return *arr_[0]; }
        T &back(){ return *arr_[size_ - 1 ]; }
        T &front(){ return *arr_[0]; }

        void resize(size_t kap) {
            while(kap < size_) realloc();
            size_ = kap;
        }

        MojVector& pop_back(){
            --size_;
        }

        size_t capacity_(){ return capacity_; }

        T& at(int a){
            if(a>size_-1) throw std::invalid_argument{"Index is out of range"};
            auto l = arr_+a;
            return *l;
        }

        T& operator[](T a){
            return at(a);
        }

        void print() {
            for(T i = 0; i < size_; ++i)
                std::cout << this->at(i) << ", ";
            std::cout << "\b\b;" << std::endl;
        }

        MojVector operator*(int a){
            MojVector temp = *this ;
            for( int i = 0; i < temp.size_; ++i )
                temp.arr_[i] = arr_[i]*a;
            return temp;
        }

        template <typename u>
        MojVector operator+(const u& a){
            MojVector<T> temp{*this};
            if(temp.size_ != a.size_) throw std::invalid_argument{"Razlicite velicine!"};
            for(int i = 0; i < size_; ++i){
                temp.arr_[i] = arr_[i] + a.arr_[i];
            }
            return temp;
        }

        MojVector& operator++(){
            auto lamb = [](T a){ return ++a; };
            kopi(*this, *this, lamb);
            return *this;
        }

        MojVector operator++(int){
            auto lamb = [](T a){ return ++a; };
            kopi(*this, *this, lamb);
            return *this;
        }

        //kopira iz a u b po definisanoj transformaciji :
        template<typename c1, typename c2>
        void kopi(c1& b, const c2& a, std::function<T(T)>&& l = [](T a){ return a;}){
            size_t broj = 0;
            while(broj < b.size_ && broj < a.size_){
                b.arr_[broj] = l(a.arr_[broj]);
                ++broj;
            }
        }

        void push_back(T a){
            if(size_==capacity_) reloc();
            arr_[size_] = a;
            ++size_;
        }

        void reloc(){
            MojVector temp{*this};
            capacity_*=2;
            delete [] arr_;
            arr_ = new T[capacity_];
            kopi(*this, temp);
        }

        void pop_back() { --this.size_; }

        bool operator==(const MojVector &other) const {
            if( size_ != other.size_) return false;
            for (size_t i = 0; i < size_; ++i)
                if( arr_[i] != other.arr_[i] ) return false;
            return true;
        }
        bool operator!=(const MojVector &other) const{
            return !(*this==other);
        }

        class Iterator;
        Iterator begin() const {
            return Iterator(arr_[0]);
        }
        Iterator end() const {
            return Iterator(arr_[size_-1]);
        }
        Iterator find(const T &element) const{
            auto it = begin();
            while( it != end() )
                if( *it == element ) break;
            return it;
        }
        MojVector &insert(Iterator ins, T element){
            auto it = end();
            while( it != ins ){
                *it = *(it-1);
                --it;
            }
            *ins = element;
            ++size_;
            return *this;
        }
        Iterator erase(Iterator pos){
            for( auto it = pos+1; it < end(); ++it )
            *(it-1) = *it;
            --size_;
            return pos;
        }
        Iterator erase(Iterator beginIt, Iterator endIt){
            while( endIt != end() ){
                *beginIt = *endIt;
                ++beginIt;
                ++endIt;
            }
            size_ -= endIt - beginIt;
        }

        T& front() const { return *arr_[0]; }
        T& back() const { return *arr_[size_-1]; }

    private:
        size_t size_;
        size_t capacity_;
        T* arr_{nullptr};
};

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T> {
public:
  Iterator(T *ptr);
  T &operator*() const { return *ptr_; }
  T *operator->() const { return *ptr_; }
  Iterator &operator++() { ++ptr_; return ptr_; }
  Iterator operator++(int) { 
      auto temp = ptr_;
      ++ptr_;
      return temp;
    }
  Iterator &operator--() { --ptr_; return ptr_; }
  Iterator operator--(int){
    auto temp = ptr_;
    --ptr_;
    return temp;
  }
  Iterator operator+(size_t index){ auto temp = ptr_ + index; return temp; }
  Iterator operator-(size_t index){ auto temp = ptr_ - index; return temp; }
  size_t operator-(Iterator other){ return other.ptr_ - ptr_ };

  bool operator==(const Iterator &it) const { return ptr_ == it.ptr_; }
  bool operator!=(const Iterator &it) const { return !(ptr_ == it.ptr_); }
  bool operator<(const Iterator &it) const { return ptr_ < it.ptr_; }

  ~Iterator();

private:
  T *ptr_;
};

*/