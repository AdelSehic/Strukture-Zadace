#include <iostream>
#include "postfixCalc.hpp"

int main(int argc, char const *argv[]){

    postfixCalc<int> a;

    while(std::cin) std::cout << a.izracunaj(std::cin) << std::endl;
    
    return 0;
}
