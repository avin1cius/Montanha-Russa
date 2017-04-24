#include <iostream>
#include "parque.h"
#include "carro.h"
#include "passageiro.h"
#include <thread>
#include <atomic>
#include <pthread.h>

using namespace std;

int main() {

    int numPessoas;
    std::cout << "Digite o numero de pessoas no parque" << std::endl;
    std::cin >> numPessoas;

    Parque parque( numPessoas );

    Carro carro( parque );

    Passageiro pass( carro );

    std::thread tCarro = std::thread( &Carro::run, carro );
    std::thread *tPassageiro = new std::thread [numPessoas];

    for (int i = 1; i <= numPessoas; i++) { 
        tPassageiro[i] = std::thread( &Passageiro::run, pass, i );
    }

    for (int i = 1; i <= numPessoas; i++) { 
        tPassageiro[i].join();
    }
    
    return 0;
}