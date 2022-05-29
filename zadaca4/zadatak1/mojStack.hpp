#include "forward_list_sentinel.hpp"

template<typename T>
class stack{
public:
    T& top();
    template<typename U>
    stack<T>& push(U&&);
    stack<T>& pop();
    size_t size();

    void ispis(){
        for(auto it = stog.begin(); it!=stog.end();++it) std::cout << *it << ' ';
        std::cout << std::endl;
    }

private:
    list<T> stog;
};

template<typename T>
T& stack<T>::top(){
    return stog.front();
}
template<typename T>
template<typename U>
stack<T>& stack<T>::push(U&& elem){
    stog.push_front(std::forward<U>(elem));
    return *this;
}
template<typename T>
stack<T>& stack<T>::pop(){
    stog.pop_front();
    return *this;
}
template<typename T>
size_t stack<T>::size(){
    return stog.size();
}