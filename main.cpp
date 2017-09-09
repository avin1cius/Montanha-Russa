#include <iostream>
#include "passageiro.h"

using namespace std;

int main() {

    int numPessoas;
    std::cout << "Digite o numero de pessoas no parque" << std::endl;
    std::cin >> numPessoas;

    Parque *parque = new Parque( numPessoas );

    Atomico *atomic = new Atomico();

    Carro *carro = new Carro( *parque , *atomic );

    Passageiro pass( *carro, *atomic );

    std::thread tCarro = std::thread( &Carro::run, carro );

    std::thread *tPassageiro = new std::thread [numPessoas];

    for ( int i = 0; i < numPessoas; i++ ) {
        tPassageiro[i] = std::thread( &Passageiro::run, pass, i+1 );
    }

    for ( int i = 0; i < numPessoas; i++ ) {
        tPassageiro[i].join();
    }

    tCarro.join();

    delete carro;

    return 0;
}
