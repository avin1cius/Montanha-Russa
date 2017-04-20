#include <iostream>
#include "passageiro.h"

void main() {

    int numPessoas;
    cout << "Digite o numero de pessoas no parque" << endl;
    cin >> numPessoas;

    Parque parque( numPessoas );

    Carro carro( &parque );
    
    carro.setMaxVoltas( 10 );
    carro.run;

    return 0;
}