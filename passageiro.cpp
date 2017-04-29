#include "passageiro.h"

int randTime, ficha = 1;

Passageiro::Passageiro( Carro &c, Atomico &a ) : carro(c), atomic(a) {
}

Passageiro::~Passageiro() {
}

void Passageiro::entraNoCarro() {
    atomic.print_mutex.lock();
    std::cerr << "Pass " << id << " entrou " << std::endl;
    atomic.print_mutex.unlock();

    carro.sumNumPassageiros( 1 );

    if ( carro.getNumPassageiros() < carro.getCapacidade()) //
        carro.next++;

    while ( !carro.lock );
}

void Passageiro::esperaVoltaAcabar() {
    //std::this_thread::sleep_for( std::chrono::seconds( TEMP_VOLTA ));
    while ( carro.lock );
}

void Passageiro::saiDoCarro() {
    //atomic.print_mutex.lock();
    randTime = ( float (rand()) / float (RAND_MAX) ) * 10 + 5; //variando entre 5 e 15
    //atomic.print_mutex.unlock();

    atomic.print_mutex.lock();
    std::cerr << "Pass " << id << " saiu do carro e foi passear por " << randTime << " segundos" << std::endl;
    atomic.print_mutex.unlock();

    carro.sumNumPassageiros( -1 ); //decrementa numPassageiros
}

void Passageiro::passeiaPeloParque() {
    std::this_thread::sleep_for( std::chrono::seconds(randTime)); //dorme por randTime segundos
}

bool Passageiro::parqueFechado() {
	if ( carro.getNVoltas() <= MAX_NUM_VOLTAS )
		return false;

	return true;
}

void Passageiro::run( int i ) {
    id = i;

	while (!parqueFechado()) {

        if( ficha == MAX_NUM_VOLTAS * carro.getCapacidade() + 1 )
            break;

        carro.turn[id] = atomic.FA( ficha, 1 );

        atomic.print_mutex.lock();
        std::cerr << "Pass " << id << " ficha " << carro.turn[id] << std::endl;
        atomic.print_mutex.unlock();

        while ( carro.turn[id] != carro.next );
		entraNoCarro(); //aguarda Carro:esperaEncher()

		esperaVoltaAcabar(); //aguarda Carro:daUmaVolta()

		//while ( atomic.TS( carro.lock ));
		atomic.lock_mutex.lock();
		saiDoCarro(); // protocolo de saida
		atomic.lock_mutex.unlock();
		//carro.lock = false;

		passeiaPeloParque(); // secao nao critica
	}

	Parque *parque = &carro.getParque();

	atomic.print_mutex.lock();
	std::cerr << "Pass " << id << " saiu do parque" << std::endl;
    
	parque->sumNumPessoas( -1 ); // decrementa o numero de pessoas no parque
    atomic.print_mutex.unlock();
}
