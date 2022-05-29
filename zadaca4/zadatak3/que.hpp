#include "forward_list_sentinel.hpp"

template <typename T>
class que{
public:
    template<typename U>
    que<T>& enque(U&&);
    T deque();
    T& front();
    T& back();
    size_t size();

    void print(){
        for(auto it = kju.begin(); it!=kju.end(); ++it) std::cout << *it << ' ';
        std::cout << std::endl;
    }

private:
    list<T> kju;
};

template<typename T>
template<typename U>
que<T>& que<T>::enque(U&& elem){kju.push_front(std::forward<U>(elem)); return *this;}

template<typename T>
T que<T>::deque(){auto temp = front(); kju.pop_back(); return temp;}

template<typename T>
T& que<T>::front(){ return kju.back(); }

template<typename T>
T& que<T>::back(){return kju.front();}

template<typename T>
size_t que<T>::size(){return kju.size();}
