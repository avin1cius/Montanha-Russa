#include "passageiro.h"

int randTime, ficha = 1;

Passageiro::Passageiro(Carro &c) : carro(c) {
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    carro.sumNumPassageiros( 1 );
    std::cerr << "Pass " << id << " entrou " << std::endl;

    if ( carro.getNumPassageiros() < carro.getCapacidade()) //
        carro.next++;

    while ( !carro.lock );
}

void Passageiro::esperaVoltaAcabar() {
    //std::this_thread::sleep_for( std::chrono::seconds( TEMP_VOLTA ));
    while ( carro.lock );
}

void Passageiro::saiDoCarro() {
    carro.sumNumPassageiros( -1 ); //decrementa numPassageiros
    std::cerr << "Pass " << id << " saiu do carro" << std::endl;
}

void Passageiro::passeiaPeloParque() {
    randTime = ( float (rand()) / float (RAND_MAX) ) * 10 + 5; //variando entre 5 e 15
    std::cerr << "Pass " << id << " passeando por " << randTime << " segundos" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds(randTime)); //dorme por randTime segundos
}

bool Passageiro::parqueFechado() {
	if ( carro.getNVoltas() <= MAX_NUM_VOLTAS )
		return false;

	return true;
}

void Passageiro::run( int i ) {
    id = i;

    Atomico atomic;

	while (!parqueFechado()) {

        if( ficha == MAX_NUM_VOLTAS * carro.getCapacidade() + 1 )
            break;

        carro.turn[id] = atomic.FA( ficha, 1 );
        std::cerr << "Pass " << id << " ficha " << carro.turn[id] << std::endl;

        while ( carro.turn[id] != carro.next );
		entraNoCarro(); //aguarda Carro:esperaEncher()

		esperaVoltaAcabar(); //aguarda Carro:daUmaVolta()
        //std::cerr<<"L"<<carro.lock<<"CK"<<std::endl;
        while ( atomic.TS( carro.lock ));
		saiDoCarro(); // protocolo de saida
		carro.lock = false;

		passeiaPeloParque(); // secao nao critica
	}

	Parque *parque = &carro.getParque();
	std::cerr << "Pass " << id << " saiu do parque" << std::endl;
	parque->sumNumPessoas( -1 ); // decrementa o numero de passageiros no parque
}
