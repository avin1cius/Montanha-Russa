#include "passageiro.h"

#define MAX_NUM_VOLTAS 10

int randTime, ficha = 1;

Passageiro::Passageiro(Carro &c) : carro(c) {
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    carro.sumNumPassageiros( 1 );
    if ( carro.getNumPassageiros() < carro.getCapacidade()) //
        carro.next++;
}

void Passageiro::esperaVoltaAcabar() {
    std::this_thread::sleep_for( std::chrono::seconds( 5 ));
}

void Passageiro::saiDoCarro() {
    carro.sumNumPassageiros( -1 ); //decrementa numPassageiros
}

void Passageiro::passeiaPeloParque() {
    randTime = ( float (rand()) / float (RAND_MAX) ) * 10 + 5; //variando entre 5 e 15
    std::cout << "Passageiro " << id << " passeando por " << randTime << " segundos" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds(randTime)); //dorme por randTime segundos
}

bool Passageiro::parqueFechado() {
	if ( carro.getNVoltas() < MAX_NUM_VOLTAS )
		return false;

	return true;
}

void Passageiro::run( int i ) {
    id = i;

    David david;

	while (!parqueFechado()) {

        carro.turn[id] = david.FA( ficha, 1 );
        std::cout << "Passageiro " << id << " pegou ficha " << carro.turn[id] << std::endl;
        while ( carro.turn[id] != carro.next );
        std::cout << "Passageiro " << id << " entrou " << std::endl;
		entraNoCarro(); // protocolo de entrada
        while ( !carro.lock ); //aguarda Carro:esperaEncher()

		esperaVoltaAcabar();
        while ( carro.lock ); //aguarda Carro:daUmaVolta()
        //std::cout << "Passageiro " << id << " vomitou " << std::endl;

        while ( david.TS( carro.lock ));
        std::cout << "Passageiro " << id << " saiu do carro" << std::endl;
		saiDoCarro(); // protocolo de saida
        carro.lock = false;

		passeiaPeloParque(); // secao nao critica
	}

	// decrementa o numero de passageiros no parque
}
