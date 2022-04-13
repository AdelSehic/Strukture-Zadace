#include <iostream>
#include <cmath>

int main(int argc, char const *argv[])
{

    std::cout << pow(5,2) << std::endl;

    for (size_t i = 0; i < 20; ++i)
    {
        std::cout << pow(5,i) << std::endl;
    }
    
    return 0;
}