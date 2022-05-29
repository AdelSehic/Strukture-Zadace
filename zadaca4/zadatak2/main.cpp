#include "mojStack.hpp"
#include <iostream>

stack<int> stog;

bool otvorenaZagrada(char a){
    return a=='<'||a=='('||a=='['||a=='{';
}

void ubaci(char a){
    int k = 0;
    switch (a){
        case '<': case '>' : k = 1; break;
        case '(': case ')' : k = 2; break;
        case '[': case ']' : k = 3; break;
        case '{': case '}' : k = 4; break;
        default: throw std::logic_error{"What are you tring to push?"}; break;
    }
    if(otvorenaZagrada(a)){
        if(stog.top() <= k) throw std::logic_error{"Respect the hierarchy!"};
        stog.push(k);
    } else {
        k=-k;
        if(stog.top()+k) throw std::logic_error{"Respect the hierarchyj!"};
        stog.pop();
    }
}

int main(int argc, char const *argv[])
{
    bool valja = true;
    stog.push(10);

    try{
        char unos;
        while(std::cin>>unos) ubaci(unos);
    }catch(const std::logic_error& a){
        valja = false;
        std::cout << a.what() << std::endl;    
    }

    if(stog.size()!=1) valja = false;
    std::cout << (valja ? "valja" : "nevalja") << std::endl;

    return 0;
}
