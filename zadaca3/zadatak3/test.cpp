#include "lista.hpp"

list<int> tempLista(){
    return list<int>{10,15,20,25,50};
}

int main(int argc, char const *argv[])
{

    list<int> p = tempLista();

    list<int> k{p};

    k.push_back(1).push_back(1).push_back(1).pop_front();
    
    return 0;
}
