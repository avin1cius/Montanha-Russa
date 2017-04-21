#include "passageiro.h"

#define MAX_NUM_VOLTAS 100

int randTime; 

Passageiro::Passageiro(Carro &c) : carro(c) {
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    turn[id] = std::atomic_fetch_add( &ficha, 1 );
    while (turn[id] != next);
    if ( carro.getNumPassageiros() < carro.getCapacidade() ) {//verifica se numPassageiros < capacidade e entra e incrementa
        carro.sumNumPassageiros( 1 );
        ++next;
    }

}

void Passageiro::esperaVoltaAcabar() {
    std::this_thread::sleep_for( std::chrono::seconds( 5 ));
    while ( lock ); //espera Carro::daUmaVolta() liberar
}

void Passageiro::saiDoCarro() {
    while ( std::atomic_flag_test_and_set( &lock ));
    carro.sumNumPassageiros( -1 ); //decrementa numPassageiros
    lock = false;
}

void Passageiro::passeiaPeloParque() {
    randTime = ( float (rand()) / float (RAND_MAX) ) * 10 + 5; //variando entre 5 e 15
    std::this_thread::sleep_for( std::chrono::seconds(randTime) ); //dorme por randTime segundos
}

bool Passageiro::parqueFechado() {
	if (carro.getNVoltas() <= MAX_NUM_VOLTAS)
		return false;

	return true;
}

void Passageiro::run( int i ) {
    id = i;
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de passageiros no parque
}
