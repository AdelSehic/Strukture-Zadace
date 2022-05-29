#include "mojStack.hpp"

int main(int argc, const char** argv) {
    
    stack<int> k;

    for(auto i = 0; i < 100000000; ++i) k.push(i);

    for (size_t i = 0; i < 100000000; ++i)
    {
        k.pop();
    }
    
 
    return 0;
}