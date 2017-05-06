#include "carro.h"

int Carro::capacidade = 0;

Carro::Carro( Parque &p, Atomico &a ) : parque(p), atomic(a) {
	voltas = 0;
	Carro::capacidade = p.getNumPessoas() / 2;
	numPassageiros = 0;
	lock = false;
	next = 1;
	turn = new int [p.getNumPessoas() + 1];
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
    while ( numPassageiros != capacidade );

    atomic.print_mutex.lock();
    std::cerr << "Carro cheio" << std::endl;
    atomic.print_mutex.unlock();

    lock = true;
}

void Carro::daUmaVolta() {
    atomic.print_mutex.lock();
    std::cerr << voltas + 1 << "ª volta iniciada" << std::endl;
    atomic.print_mutex.unlock();

    std::this_thread::sleep_for( std::chrono::seconds( TEMP_VOLTA )); //dorme alguns segundos

    atomic.print_mutex.lock();
    std::cerr << voltas + 1 << "ª volta finalizada" << std::endl;
    atomic.print_mutex.unlock();

    lock = false;
}

void Carro::esperaEsvaziar() {
    while ( numPassageiros );

    atomic.print_mutex.lock();
    std::cerr << "Carro vazio" << std::endl << std::endl;
    atomic.print_mutex.unlock();
}

void Carro::sumNumPassageiros( int num) {
    numPassageiros += num;
}

int Carro::getNVoltas() {
	return voltas;
}

int Carro::getCapacidade() {
    return capacidade;
}

int Carro::getNumPassageiros() {
    return numPassageiros;
}

Parque &Carro::getParque() {
	return parque;
}

void Carro::run() {
	while ( voltas != MAX_NUM_VOLTAS ) {
		esperaEncher();  //aguarda Passageiro::entraNoCarro()

		daUmaVolta();

		esperaEsvaziar(); //aguarda Passageiro::saiDoCarro() zerar numPassageiros

		++voltas;
		++next;
	}

	while ( parque.getNumPessoas());

    atomic.print_mutex.lock();
	std::cerr << std::endl << "Parque fechou" << std::endl;
	atomic.print_mutex.unlock();
}
