#include "carro.h"

int Carro::capacidade = 0;

Carro::Carro( Parque &p ) : parque(p) {
	voltas = 0;
	Carro::capacidade = p.getNumPessoas() / 2;
	numPassageiros = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {
    while ( numPassageiros != capacidade ); //aguarda ate numPassageiros == capacidade
	}

void Carro::daUmaVolta() {
    std::this_thread::sleep_for( std::chrono::seconds( 5 )); //dorme alguns segundos
}

void Carro::sumNumPassageiros( int num) {
    numPassageiros += num;
}

void Carro::esperaEsvaziar() {
    while ( numPassageiros ); //aguarda ate numPassageiros == 0
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
		esperaEncher();
		lock = false;
		daUmaVolta();
		lock = true;

		esperaEsvaziar();

		voltas++;
	}
}