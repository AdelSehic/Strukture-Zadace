#include <iostream>
#include "MojVektor.hpp"
#include <vector>

int main(int argc, char const *argv[])
{
    MojVector<int> mojNiz{1, 2};
    mojNiz.resize(5);

    for(auto var : mojNiz)
    {
        std::cout << var << ' ';
    }

    return 0;
}