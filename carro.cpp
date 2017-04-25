#include "carro.h"

int Carro::capacidade = 0;

Carro::Carro( Parque &p ) : parque(p) {
	voltas = 1;
	Carro::capacidade = p.getNumPessoas() / 2;
	numPassageiros = 0;
	lock = false;
	next = 1;
	turn = new int [p.getNumPessoas() + 1];
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
    while ( Carro::numPassageiros != capacidade );
    std::cout << "Encheu" << std::endl;
}

void Carro::daUmaVolta() {
    std::cout << voltas << "ª volta iniciada" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds( 10 )); //dorme alguns segundos
    std::cout << voltas << "ª volta finalizada" << std::endl;
}

void Carro::sumNumPassageiros( int num) {
    Carro::numPassageiros += num;
}

void Carro::esperaEsvaziar() {
    while ( numPassageiros );
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
	while (parque.getNumPessoas() > 0) {
		esperaEncher();  //aguarda Passageiro::entraNoCarro()
		lock = true;
		daUmaVolta();
		lock = false;

		esperaEsvaziar(); //aguarda Passageiro::saiDoCarro() zerar numPassageiros

		++voltas;
		++next;
	}
}
