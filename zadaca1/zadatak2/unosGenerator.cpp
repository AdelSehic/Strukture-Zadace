#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main() {

    std::ifstream imena("imena.txt");
    std::ofstream ulaz("ulaz.txt");
    // int randomGodine, randomIskustvo, randomAuto;
    // double randomVrijeme;

    std::random_device dev;
    std::mt19937 generator(dev());
    std::uniform_int_distribution<std::mt19937::result_type> godine(18,40);
    std::uniform_int_distribution<std::mt19937::result_type> iskustvo(1,10);
    std::uniform_real_distribution<double> vrijeme(63,120);
    std::uniform_int_distribution<std::mt19937::result_type> car(1,3);


    while(imena){
        std::string ime, prezime;
        imena >> ime >> prezime;
        ulaz << ime << ' ' << prezime << ' ' << godine(generator) << ' ' << iskustvo(generator) << ' ' << vrijeme(generator) << ' ' << car(generator) << '\n';
    }

    imena.close();
    ulaz.close();

    return 0;
}