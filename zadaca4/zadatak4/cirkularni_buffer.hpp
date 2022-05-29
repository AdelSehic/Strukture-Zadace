#include <cstddef>

template <typename T>
class circularBuffer{
public:
    circularBuffer(size_t);
    circularBuffer(const circularBuffer<T>&);
    circularBuffer(circularBuffer<T>&&);
    circularBuffer<T>& operator=(const circularBuffer<T>&);
    circularBuffer<T>& operator=(circularBuffer<T>&&);
    ~circularBuffer();

    template<typename U>
    circularBuffer<T>& push(U&&);
    T pop();
    
    size_t size(){ return size_; };
    size_t capacity(){ return capacity_; };
    bool empty(){ return !size_; };

    T& front();
    T& back();
    T& front() const;
    T& back() const;

    void print(){
        for(int i = 0; i < capacity_; ++i){
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    void print2(){
        for(int i = begin; i != end; i = (i+1) % capacity_ ){
            std::cout << arr[i] << ' ';
        }
        std::cout << std::endl;
    }

private:
    size_t capacity_;
    size_t size_;
    T* arr;
    size_t begin, end;
};

template<typename T>
circularBuffer<T>::circularBuffer(size_t cap) 
: capacity_{cap}, size_{0}, arr{new T[cap]}, begin{0}, end{0} {}

template<typename T>
circularBuffer<T>::circularBuffer(const circularBuffer<T>& other) 
: capacity_{other.capacity_}, size_{other.size_}, arr{new T[capacity_]}, begin{other.begin}, end{other.end} {
    std::copy(other.arr, other.arr + other.capacity_, arr);
}

template<typename T>
circularBuffer<T>::circularBuffer(circularBuffer<T>&& other) 
: capacity_{other.capacity_}, size_{other.size_}, arr{other.arr}, begin{other.begin}, end{other.end} {
    other.arr = nullptr;
}

template<typename T>
circularBuffer<T>& circularBuffer<T>::operator=(const circularBuffer<T>& other){
    delete [] arr;
    capacity_ = other.capacity_;
    size_ = other.size_;
    begin = other.begin;
    end = other.end;
    arr = new T[capacity_];
    std::copy(other.arr, other.arr + other.capacity_, arr);
    return *this;
}

template<typename T>
circularBuffer<T>& circularBuffer<T>::operator=(circularBuffer<T>&& other){
    capacity_ = other.capacity_;
    size_ = other.size_;
    begin = other.begin;
    end = other.end;
    std::swap(arr, other.arr);
    return *this;
}

template<typename T>
circularBuffer<T>::~circularBuffer(){
    delete [] arr;
}

template<typename T>
template<typename U>
circularBuffer<T>& circularBuffer<T>::push(U&& elem){
    if(size_ == capacity_) throw std::out_of_range{"Pun ti je bafer kralju moj"};
    arr[end] = std::forward<U>(elem);
    end = (end+1) % capacity_;
    ++size_;
    return *this;
}

template<typename T>
T circularBuffer<T>::pop(){
    if(!size_) return;
    auto temp = arr[begin];
    begin = (begin+1) % capacity_;
    --size_;
    return temp;
}
template<typename T>
T& circularBuffer<T>::front() { return arr[begin]; }
template<typename T>
T& circularBuffer<T>::back() { return arr[end]; }
template<typename T>
T& circularBuffer<T>::front() const { return arr[begin]; }
template<typename T>
T& circularBuffer<T>::back() const { return arr[end]; }