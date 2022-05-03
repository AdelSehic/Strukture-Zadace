#include <iostream>
#include <algorithm>
#include <fstream>
#include "sorted_forward_list.hpp"

int main(int argc, char const *argv[])
{
    list<int> k{1,5,3,35,67,23,234,41,15,-1,2,-515,51,5,-10};

    auto p = k.dajbek();

    k.ispis();

    std::cout << "BEK : " << p->data << std::endl;

    return 0;
}