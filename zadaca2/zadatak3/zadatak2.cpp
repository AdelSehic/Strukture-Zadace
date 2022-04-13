#include <iostream>
#include "MojVektor.hpp"
#include <algorithm>

class osoba{
    public:

        osoba() = default;
        osoba( std::string ime, std::string prezime, int starost )
        : ime_{ime}, prezime_{prezime}, godineStarosti_{starost} {};

        osoba(const osoba& other) : ime_{other.ime_}, prezime_{other.prezime_}, godineStarosti_{other.godineStarosti_} {};

        void setIme( std::string a ) { ime_ = a; }
        std::string getIme() const { return ime_; }
        void setPrezime( std::string a ) { prezime_ = a; }
        std::string getPrezime() const { return prezime_; }
        void setStarost( int a ) { godineStarosti_ = a; }
        int getStarost() const { return godineStarosti_; }
    private:
        std::string ime_;
        std::string prezime_;
        int godineStarosti_;
};

// da ne moram pisati settere i gettere koristit cu struct
struct automobil{

    // automobil( std::string model, std::string boja, int godina )
    // : model_{model}, boja_{boja}, godinaProizvodnje_{godina} {};

    automobil() = default;
    automobil( const std::string& model, const std::string& boja,const int& godina )
    : model_{model}, boja_{boja}, godinaProizvodnje_{godina} {};
    
    std::string model_;
    std::string boja_;
    int godinaProizvodnje_;
};

// lista automobila dostupinuh ucesnicima:
MojVector<automobil> auta{ {"Ford GT", "plava", 2004}, {"Ferrari F40", "crvena", 1989}, {"Mercedes AMG GT", "silver", 2016} };

class vozac : public osoba {
    public:
        vozac() = default;
        vozac(std::string ime, std::string prezime, int starost, int staz, double vrijeme, int model )
        : osoba{ ime, prezime, starost }, godineStaza_{staz}, vrijeme_{vrijeme}, avto{ &auta[model-1] } {}

        vozac( const vozac& other )
        : osoba{ other.getIme(), other.getPrezime(), other.getStarost() }, godineStaza_{other.getStaz()},
        vrijeme_{other.getVrijeme()}, avto{ other.avto } {};

        std::string& imeAuta() { return avto -> model_; }

        int getStaz() const { return godineStaza_; }
        double getVrijeme() const { return vrijeme_; }
        automobil& staVozi() const { return *avto; }

        bool operator<( const vozac& drugi ) { return vrijeme_ < drugi.vrijeme_; }

    private:
        int godineStaza_;
        automobil* avto{nullptr}; // ne moze auto
        double vrijeme_; // u sekundama
};

std::ostream& operator<<( std::ostream& out, const automobil& car ){
    out << "Automobil: " << car.model_ << ", " << car.boja_ << ", " << car.godinaProizvodnje_ << '.' << std::endl;
    return out;
}

std::ostream& operator<<( std::ostream& out, const vozac& voz ){
    out << voz.getIme() << ' ' << voz.getPrezime() << ", " << voz.getStarost() << ", " << voz.getStaz() << ", " << voz.getVrijeme() << std::endl;
    out << voz.staVozi();
    return out;
}

int main(int argc, char const *argv[])
{
    // vozac adel{ "Adel", "Sehic", 21, 2, 57.120 };
    // auta.push_back({"Ford GT", "plava", 2004});
    // auta.push_back({"Ferrari F40", "crvena", 1989});
    // auta.push_back({"Mercedes AMG GT", "silver", 2016});

    std::cout << "zavrseni push backovi" << std::endl << std::endl;

    MojVector<vozac> vozaci;

    int brojVoz = 0;
    std::cout << "Unesite broj vozaca koji ucestvuju: ";
    std::cin >> brojVoz;
    std::cout << std::endl;

    while(brojVoz > 0){
        std::string ime, prezime;
        int star, staz, modelAuta;
        double vrijeme;

        std::cin >> ime >> prezime >> star >> staz >> vrijeme >> modelAuta;

        vozac temp{ime, prezime, star, staz, vrijeme, modelAuta};
        vozaci.push_back( temp );

        --brojVoz;
    }

    std::sort( vozaci.begin(), vozaci.end() );

    for( auto&& i : vozaci ) {
        std::cout << i << '\n';
    }
    
    return 0;
}