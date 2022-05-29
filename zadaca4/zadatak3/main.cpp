#include "que.hpp"
#include "forward_list_sentinel.hpp"
#include <ios>
#include <limits>

int main(int argc, const char** argv) {
    short int odabir;
    que<long int> red;
    long int racun = 0;
    long int unos;
    while(odabir != 6 && std::cin){
        odabir = 0;
        std::cout<< "Actions:\n\t1. New transaction\n\t2. Apply transaction\n\t3. Pending transaction\n\t4. Discard pending trnsaction\n\t5. Ballance\n\t Exit\nYour choice: ";

        while(std::cin >> odabir && !(odabir<7 && odabir>0)){std::cout << "Try again: ";};
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

        switch (odabir){
        case 1:
            std::cout << "Unesite novu tranzakciju: ";
            std::cin>>unos;
            red.enque(unos);
            break;
        case 2:
            racun += red.deque();
            break;
        case 3:
            std::cout << "Pending transaction: " << red.front() << std::endl;
            break;
        case 4:
            red.deque();
            break;
        case 5:
            std::cout << "Stanje racuna: " << racun << std::endl;
            break;
        default:
            break;
        }
    }
    return 0;
}