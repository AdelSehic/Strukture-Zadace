#pragma once

#include <iostream>
#include <initializer_list>

template <typename T>
class list{
    public:

    // rule of 6 :
    list();
    list(const std::initializer_list<T>&);
    list(const list<T>&);
    list(list<T>&&);
    list<T>& operator=(const list<T>&);
    list<T>& operator=(list<T>&&);
    ~list<T>();

    // iterator stuff
    class iterator;
    class const_iterator;
    iterator begin();
    iterator end();
    iterator begin() const;
    iterator end() const;
    
    // method(man)s :
    list<T>& push_back(const T&);
    list<T>& push_front(const T&);
    list<T>& pop_back();
    list<T>& pop_front();
    void clear();
    size_t size();
    bool empty();
    T& front();
    T& back();
    void insert(iterator, T);
    void erase(iterator);

    // O(n) :
    T& at(size_t);
    const T& at(size_t) const;
    bool operator==(const list<T>&);
    bool operator!=(const list<T>&);
    iterator find(const T&);

    void ispis(){
        if(!size_) return;
        auto temp = sentinel -> next;
        while( temp != sentinel ){
            std::cout << temp -> data << ' ';
            temp = temp -> next;
        }
        std::cout << std::endl;
    }

    private:
    struct node{

        node() = default;
        node(node* a, node* b) : next{a}, previous{b} {}
        node(node* a, node* b, T c) : next{a}, previous{b}, data{c} {}

        node* next;
        node* previous;
        T data;
    };
    
    node* sentinel = new node{ nullptr, nullptr};
    size_t size_;
};

// C L A S S   I M P L E M E N T A T I O N

// constructors :

template <typename T>
list<T>::list(){
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
    size_ = 0;
}

template <typename T>
list<T>::list(const list<T>& other) {
    sentinel -> next = sentinel;
    sentinel -> previous = sentinel;
    for( auto it = other.begin(); it != other.end(); ++it ){
        push_back(*it);
    }
    size_ = other.size_;
}

template <typename T>
list<T>::list(list<T>&& other) : sentinel{ new node{other.sentinel -> next, other.sentinel -> previous} }, size_{other.size_} {
    sentinel -> next -> previous = sentinel;
    sentinel -> previous -> next = sentinel;
    other.sentinel -> next = other.sentinel -> previous = other.sentinel;
    other.size_ = 0;
}

template <typename T>
list<T>& list<T>::operator=(const list<T>& other){
    if( this == &other ) return *this;
    clear();
    for( auto it = other.begin(); it != other.end(); ++it )
        push_back(*it);
    size_ = other.size_;
    return *this;
}

template <typename T>
list<T>& list<T>::operator=(list<T>&& other){
    clear();
    sentinel -> next = other.sentinel -> next;
    sentinel -> previous = other.sentinel -> previous;
    sentinel -> next -> previous = sentinel;
    sentinel -> previous -> next = sentinel;
    other.sentinel -> next = other.sentinel -> previous = other.sentinel;
    size_ = other.size_;
    other.size_ = 0;
    return *this;
}

template <typename T>
list<T>::~list<T>(){
    clear();
    delete sentinel;
}

template <typename T>
list<T>::list(const std::initializer_list<T>& elementi) {
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
    auto it = elementi.begin();
    auto brojac = 0;
    while (it != elementi.end())
    {
        push_back(*it);
        ++it;
        ++brojac;
    }
    size_ = brojac;
}

// methods :

template <typename T>
list<T>& list<T>::push_back(const T& element){
    node* temp = new node{ sentinel, sentinel->previous, element };
    sentinel -> previous -> next = temp;
    sentinel -> previous = temp;
    ++size_;
    return *this;
}

template <typename T>
list<T>& list<T>::push_front(const T& element){
    node* temp = new node( sentinel->next, sentinel, element );
    temp -> next -> previous = temp;
    sentinel -> next = temp;
    ++size_;
    return *this;
}

template <typename T>
list<T>& list<T>::pop_back(){
    sentinel -> previous = sentinel -> previous -> previous;
    delete sentinel -> previous -> next;
    sentinel -> previous -> next = sentinel;
    --size_;
    return *this;
}

template <typename T>
list<T>& list<T>::pop_front(){
    sentinel -> next = sentinel -> next -> next;
    delete sentinel -> next -> previous;
    sentinel -> next -> previous = sentinel;
    --size_;
    return *this;
}

template <typename T>
void list<T>::clear(){
    if( sentinel -> next == sentinel ) return;
    node* temp;
    while (sentinel -> next != sentinel){
        temp = sentinel -> next;
        sentinel -> next = temp -> next;
        delete temp;
    }
    sentinel -> next = sentinel -> previous = sentinel;
    size_ = 0;    
}

template <typename T>
size_t list<T>::size(){ return size_; }

template <typename T>
bool list<T>::empty(){ return !size_; }

template <typename T>
T& list<T>::at(size_t index){
    if ( index > size_ ) throw std::out_of_range{"index > size_"};
    auto it = begin();
    for (size_t i = 0; i < index; ++i)
        ++it;
    return *it;
}

template <typename T>
const T& list<T>::at(size_t index) const{ at(index); }

template <typename T>
T& list<T>::front(){ return sentinel -> next -> data; }

template <typename T>
T& list<T>::back(){ return sentinel -> previous -> data; }

template <typename T>
void list<T>::insert(iterator position, T element){
    position -> previous = new node{ position.p_, position -> previous, element };
    position -> previous -> previous -> next = position -> previous;
    ++size_;
}

template <typename T>
void list<T>::erase(iterator position){
    position -> previous -> next = position -> next;
    position -> next -> previous = position -> previous;
    delete position.p_;
    --size_;
}

template <typename T>
bool list<T>::operator==(const list<T>& other){
    if ( size_ != other.size_ ) return false;
    auto it1 = begin();
    auto it2 = other.begin();
    while( it1 != end() ){
        if( *it1 != *it2 ) return false;
        ++it1;
        ++it2;
    }
    return true;
}

template <typename T>
bool list<T>::operator!=(const list<T>& other){ return !( *this == other ); }

template <typename T>
typename list<T>::iterator list<T>::find(const T& element){
    auto it = begin();
    while( *it != element && it != end() ) ++it;
    return it;
}

// I T E R A T O R :

template <typename T>
class list<T>::iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    public:
    friend class list<T>;

    iterator(node* p) : p_{p} {}

    bool operator==(iterator const& other) const { return p_ == other.p_; }
    bool operator!=(iterator const& other) const { return !(*this == other); }

    iterator& operator++() { p_ = p_->next; return *this; }
    iterator& operator--() { p_ = p_->prev; return *this; }
    iterator operator++(int) { 
        auto temp = iterator(p_);
        p_ = p_ -> next;
        return temp;
    }
    iterator operator--(int) { 
        auto temp = iterator(p_);
        p_ = p_ -> previous;
        return temp;
    }
    iterator& operator+(size_t offset)
    {
        for (size_t i = 0; i < offset; ++i) 
            operator++();
        return *this;
    }
    iterator& operator-(size_t offset)
    {
        for (size_t i = 0; i < offset; ++i) 
            operator--();
        return *this;
    }

    T& operator*() const { return p_->data; }
    node* operator->() const { return p_; }
  
    private:
    node* p_;
};

// template < typename T >
// using iterator = list<T>::iterator<T>;

// template < typename T >
// using const_iterator = iterator<const T>;

template <typename T>
typename list<T>::iterator list<T>::begin(){ return iterator(sentinel -> next); };

template <typename T>
typename list<T>::iterator list<T>::end(){ return iterator(sentinel); };

template <typename T>
typename list<T>::iterator list<T>::begin() const { return iterator(sentinel -> next); };

template <typename T>
typename list<T>::iterator list<T>::end() const { return iterator(sentinel); };
