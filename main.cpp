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
    cout << "Digite o numero de pessoas no parque" << endl;
    cin >> numPessoas;

    Parque parque( numPessoas );

    Carro carro( parque );

    Passageiro pass( carro );

    atomic_flag lock;
    
    atomic<int> ficha = ATOMIC_VAR_INIT(1);

    int next = 1, *turn = new int [numPessoas];
    
    std::thread tCarro = std::thread(carro.run);
    std::thread *tPassageiro = new std::thread [numPessoas];

    for (int i = 1; i <= numPessoas; i++) { 
        tPassageiro[i] = std::thread(pass.run);
    }
    return 0;
}