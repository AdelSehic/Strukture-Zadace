#include <iostream>
#include "cirkularni_buffer.hpp"

int main(){

    circularBuffer<int> baf{10};

    baf.push(1).push(2).push(3).push(4).push(5).push(6);

    circularBuffer<int> fab{baf};

    baf.pop().pop().pop();

    baf.push(7).push(8).push(9).push(10).push(1);

    baf.print();
    baf.print2();

    fab.print();
    fab.print2();

    return 0;
}