#include "passageiro.h"

int ficha = 1;

Passageiro::Passageiro( Carro &c, Atomico &a ) : carro(c), atomic(a) {
    nvoltas = 0;
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    atomic.print_mutex.lock();
    std::cerr << "Passageiro " << id << " entrou com ficha " << carro.turn[id] << std::endl;
    atomic.print_mutex.unlock();

    carro.sumNumPassageiros( 1 );

    if ( carro.getNumPassageiros() < carro.getCapacidade() ) //
        carro.next++;

    while ( !carro.lock );
}

void Passageiro::esperaVoltaAcabar() {
    //std::this_thread::sleep_for( std::chrono::seconds( TEMP_VOLTA ));
    while ( carro.lock );
}

void Passageiro::saiDoCarro() {
    atomic.print_mutex.lock();
    randTime = ( float (rand()) / float (RAND_MAX) ) * 8 + 1; //variando entre 1 e 9
    atomic.print_mutex.unlock();

    atomic.print_mutex.lock();
    std::cerr << "Passageiro " << id << " saiu do carro e foi passear por " << randTime << " segundos" << std::endl;
    atomic.print_mutex.unlock();

    atomic.FA( carro.numPassageiros, -1 );

    nvoltas++;
}

void Passageiro::passeiaPeloParque() {
    std::this_thread::sleep_for( std::chrono::seconds(randTime)); //dorme por randTime segundos
}

bool Passageiro::parqueFechado() {
	if ( ficha != MAX_NUM_VOLTAS * carro.getCapacidade() + 1 )
		return false;

	return true;
}

void Passageiro::run( int i ) {
    id = i; 

	while ( !parqueFechado() ) {

        carro.turn[id] = atomic.FA( ficha, 1 );

        while ( carro.turn[id] != carro.next );
		entraNoCarro(); //aguarda Carro:esperaEncher()

		esperaVoltaAcabar(); //aguarda Carro:daUmaVolta()

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
	}

	Parque *parque = &carro.getParque();

	atomic.print_mutex.lock();
	std::cerr << "Passageiro " << id << " saiu do parque com " << nvoltas << " realizadas" << std::endl;
	atomic.print_mutex.unlock();

	atomic.FA( parque->numPessoas, -1 );
}
