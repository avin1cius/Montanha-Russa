#include <iostream>
#include "passageiro.h"

using namespace std;

int main() {

    int numPessoas;
    cout << "Digite o numero de pessoas no parque" << std::endl;
    cin >> numPessoas;

    Parque parque( numPessoas );

    Carro carro( parque );

    carro.setMaxVoltas( 10 );
    carro.run();

    return 0;
}