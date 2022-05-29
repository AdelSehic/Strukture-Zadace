#include "mojStack.hpp"
#include <sstream>

template <typename T>
class postfixCalc{
public:
    T izracunaj(std::istream&);
private:
    postfixCalc<T>& insert(const T&);
    postfixCalc<T>& insert(char);
    stack<T> stog;
};

template<typename T>
T postfixCalc<T>::izracunaj(std::istream& cin){
    std::string unos;
    getline(cin, unos);
    std::stringstream unosi(unos);
    while(unosi.good()){
        std::string temp;
        getline(unosi, temp, ' ');
        if(temp=="+"||temp=="-"||temp=="*"||temp=="/") insert(*(temp.c_str()));
        else insert(stoi(temp));
    }
    auto temp = stog.top();
    stog.pop();
    return temp;
}

template <typename T>
postfixCalc<T>& postfixCalc<T>::insert(const T& elem){ stog.push(elem); return *this; }

template <typename T>
postfixCalc<T>& postfixCalc<T>::insert(char operacija){
    auto temp = stog.top();
    stog.pop();
    switch (operacija)
    {
    case '+':
        stog.top()+=temp;
        break;
    case '-':
        stog.top()-=temp;
        break;
    case '*':
        stog.top()*=temp;
        break;
    case '/':
        stog.top()/=temp;
        break;
    default:
        throw std::logic_error{"Undefined"};
        break;
    }
    return *this;
}