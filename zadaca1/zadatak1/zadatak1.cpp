#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

class radnik {
    public:
        radnik( std::string i, std::string p, int bstar, int bstaz, size_t plat, std::string brojt )
            : ime{i}, prezime{p}, godineStarosti{bstar}, godineStaza{bstaz}, plata{plat}, brojTelefona{brojt} 
            {};
        void povecajPlatu ( float a ) { plata += plata*(a/100); };
        int starost () { return godineStarosti; };
        int iskustvo () { return godineStaza; };
        std::string imee() { return ime; };
        std::string prezimee() { return prezime; };
        std::string telefon() { return brojTelefona; };
        size_t placa() { return plata; };

        bool operator<( const radnik& drugi ) { 
            if ( ime != drugi.ime ) return ime < drugi.ime;
            else return prezime < drugi.prezime; 
        }

        bool operator>( const radnik& drugi ) {
            return godineStarosti > drugi.godineStarosti;
        }

    private:
        std::string ime;
        std::string prezime;
        int godineStarosti;
        int godineStaza;
        size_t plata;
        std::string brojTelefona;
}; 

std::ostream& operator<<( std::ostream& out, radnik& r ) { 
    return out << r.imee() << ',' << r.prezimee() << ',' << r.starost() << ',' << r.iskustvo() << ',' << r.placa() << ',' << r.telefon() << std::endl;  };


void unesiFajl( std::ifstream& a, std::vector<radnik>& b){
    
    std::string unos, ok;
    std::vector< std::string > temp;
    // radnik napisaoFajl{"Adel", "Sehic", 20, 0, 0, "062-225-883"};
    while( a ){
        a >> unos;
        std::stringstream unosi(unos);

        while( unosi.good() ){
            getline( unosi, ok, ',' );
            temp.push_back( ok );
        }

        b.push_back( {temp[0], temp[1], stoi(temp[2]), stoi(temp[3]), (size_t)stoi(temp[4]), temp[5]} );
        temp.clear();
    }
}

int main(int argc, char const *argv[])
{
    std::vector<radnik> vek;

    std::ifstream acme{"acme.txt"}, globex{"globex.txt"};

    unesiFajl( acme, vek );
    unesiFajl( globex, vek );
    
    acme.close();
    globex.close();

    auto it = vek.begin();

    std::ofstream penzija("penzionisani.txt");
    while( it != vek.end() ){
        if( it -> iskustvo() > 15 ) it -> povecajPlatu(20);
        if( it -> starost() > 54 ) { 
            penzija << *it;
            vek.erase( it );
        }
        ++it;
    }
    penzija.close();

    std::sort( vek.begin(), vek.end(), []( radnik a, radnik b ){ return a > b; } );
    while ( it != vek.end() - 15 ){ it -> povecajPlatu(10); --it; }
    std::sort( vek.begin(), vek.end() );

    std::ofstream damageINC("zaposleni.txt");
    for (auto &&i : vek) damageINC << i;
    damageINC.close();

    return 0;
}