#include "passageiro.h"

#define MAX_NUM_VOLTAS 10

int randTime, ficha = 1;

Passageiro::Passageiro(Carro &c) : carro(c) {
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    if ( carro.getNumPassageiros() < carro.getCapacidade() ) { //verifica se numPassageiros < capacidade e entra e incrementa
        carro.sumNumPassageiros( 1 ); //incrementa numPassageiros

        if( carro.getNumPassageiros() < carro.getCapacidade() ) //
            carro.next++;
    }
}

void Passageiro::esperaVoltaAcabar() {
    std::this_thread::sleep_for( std::chrono::seconds( 5 ));
}

void Passageiro::saiDoCarro() {
    carro.sumNumPassageiros( -1 ); //decrementa numPassageiros

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

    David david;

	while (!parqueFechado()) {

        carro.turn[id] = david.FA( ficha, 1 );
        while (carro.turn[id] != carro.next);
		entraNoCarro(); // protocolo de entrada
        while ( carro.lock ); //aguardar Carro:esperaEncher

		esperaVoltaAcabar();
        while ( !carro.lock );

        while ( david.TS( &carro.lock ));
		saiDoCarro(); // protocolo de saida
        carro.lock = false;

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de passageiros no parque
}
