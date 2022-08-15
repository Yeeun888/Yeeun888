#include <iostream>
#include <tuple>

using namespace std;

tuple<int, int, int> getCurrency() {

int pesos, reais, soles;

cout << "Enter number of Colombian Pesos:";
cin >> pesos;

cout << "Enter number of Brazilian Reais:";
cin >> reais;

cout << "Enter number of Peruvian Soles:";
cin >> soles;

return make_tuple(pesos, reais, soles);

}

int main(){
  auto [x,y,z]  = getCurrency();

}