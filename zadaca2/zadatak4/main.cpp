#include <iostream>
#include "MojVektor.hpp"
// #include <vector>
#include <initializer_list>
#include <cmath>

// template < typename P >
// P pow( P a, int b ){
//   P suma = 1;
//   for (size_t i = 0; i < b; ++i)
//     suma += a;
//   return suma;
// }

class polinom{
  public:
  // PRAVILO SESTORKE:
  
    polinom() = default;
    polinom(const std::initializer_list<int>& a) : elementi{a} {};
    polinom(int element) : elementi{ {0,0,element} } {}
    polinom(const MojVector<int>& element) : elementi{std::move(element)} {}

    polinom(const polinom& other){
      for( int i = 0; i < other.elementi.size(); ++i ){
        elementi.push_back( other.elementi.at(i) );
      }
    }
    polinom(polinom&& other) : elementi{std::move(other.elementi)} {}

    polinom operator=(const polinom& other){
      if ( this == &other ) return *this;
      elementi.clear();
      for( int i = 0; i < other.elementi.size(); ++i ){
        elementi.push_back( other.elementi.at(i) );
      }
      return *this;
    }
    polinom operator=(polinom&& other) {
      if ( this == &other ) return *this;
      elementi.clear();
      elementi = std::move(other.elementi);
      return *this;
    }

  // OPERATORI :

    polinom operator+(const polinom& drugi){
      auto add = [](int a, int b){ return a + b; };
      return adder(drugi, add);
    }
    polinom operator-(const polinom& drugi){
      auto subtract = [](int a, int b){ return a - b; };
      return adder(drugi, subtract);
    }
    polinom operator*(const polinom& drugi){
      MojVector<int> temp;
      temp.resize( elementi.size() + drugi.elementi.size() );
      
      for(int i = 0; i < elementi.size(); ++i){
        if( at(i) == 0) continue;
        for(int n = 0; n < drugi.elementi.size(); ++n){
          if(drugi.at(n) == 0) continue;
          temp.at( i + n ) += elementi.at(i) * drugi.elementi.at(n);
        }
      }
      return temp;
    }

    double operator()(int k){
      double suma = 0;
      for (size_t i = 0; i < size(); ++i)
      {
        suma += at(i) * pow(k,i);
      }
      return suma;
    }

    polinom operator+=(const polinom& drugi){
      polinom temp = *this + drugi;
      return temp;
    }

  // METODI :

    int& at(size_t index){ return elementi.at(index); }
    int at(size_t index) const { return elementi.at(index); }

    int size() { return elementi.size(); }
    int size() const { return elementi.size(); }

    polinom izvod(){
      auto it = elementi.begin()+1;
      size_t counter = 1;

      while(it != elementi.end()){
        if( *it == 0 ){
          ++it;
          ++counter;
        }
        else{
          *(it-1) = ( *it * counter );
          *it = 0;
          ++it;
          ++counter;
        }
      }
      return *this;
    }

  private:
    MojVector<int> elementi;

    template < typename T >
    polinom adder(const polinom& drugi, T lamb){
      auto it1 = elementi.begin();
      auto it2 = drugi.elementi.begin();
      MojVector<int> temp;
      while(true){
        if( it1 < elementi.end() && it2 < drugi.elementi.begin() ){
          temp.push_back( lamb(*it1, *it2) );
          ++it1;
          ++it2;  
        }
        else if( it1 < elementi.end() ){
          temp.push_back( lamb(*it1, 0) );
          ++it1;
        }
        else if( it2 < drugi.elementi.end() ){
          temp.push_back( lamb(0, *it2) );
          ++it2;
        }
        else
          break;
      }
      return temp;
    }
};

std::ostream& operator<<(std::ostream& out, const polinom& poli){
  // if(poli.at(0)) std::cout << poli.at(0);
  // if( poli.size() > 1 && poli.at(1) ) std::cout << poli.at(1) << "x";
  // for( int i = 2; i < poli.size(); ++i ){
  //   if(poli.at(i) == 0 ) continue;
  //   else if ( poli.at(i) > 0 ) std::cout << '+';
  //   else std::cout << poli.at(i);
  //   std::cout << "x^" << i;
  // }
  // std::cout<<std::endl;
  // return out;

  std::string ispis;
  if(poli.at(0)) ispis += std::to_string(poli.at(0));
  if( poli.size() > 1 && poli.at(1) ) {
    if( poli.at(1) > 1 ) ispis += "+";
    ispis += std::to_string(poli.at(1)) + "x";
  }
  for( int i = 2; i < poli.size(); ++i ){
    if(poli.at(i) == 0 ) continue;
    if(poli.at(i)>0) ispis+="+";
    ispis += std::to_string( poli.at(i) ) + "x^" + std::to_string(i);
  }
  std::cout << ispis << std::endl;
  return out;
}

int main() {
  polinom p1({-1,2});   // P(x): -1 + 2*x
  polinom p2(3);        // polinom drugog stepena (a + b*x + c*x^2)
  // std::cin >> p2;    // učitati sa tastature polinom drugog stepena 

  std::cout << "P1(x): " << p1 << std::endl;
  std::cout << "P2(x): " << p2 << std::endl;

  auto p3 = p1 + p2;
  auto p4 = p2 - p1;
  auto p5 = p1 * p2;

  std::cout << "P3(x): " << p3 << std::endl;
  std::cout << "P4(x): " << p4 << std::endl;
  std::cout << "P5(x): " << p5 << std::endl;

  double rezultat = p3(5);
  std::cout << "P3(5): " << rezultat << std::endl;

  p3 = p2.izvod();
  std::cout << "P2'(x): " << p3 << std::endl;

  std::cout << "P2'(5): " << p3(5) << std::endl;

  p2 += p1;
}