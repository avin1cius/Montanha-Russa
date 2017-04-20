#include "carro.h"

int Carro::capacidade = 0;;

Carro::Carro( Parque &p ) : parque(p) {
	voltas = 0;
	Carro::capacidade = p.getNumPessoas() / 2;
	nPassageiros = 0;
}

Carro::~Carro() {
}

void Carro::esperaEncher() {

}

void Carro::daUmaVolta() {

}

void Carro::esperaEsvaziar() {

}

void Carro::setMaxVoltas( int num ) {
    maxVoltas = num;
}

int Carro::getNVoltas() {
	return voltas;
}

Parque &Carro::getParque() {
	return parque;
}

void Carro::run() {
	while (parque.getNumPessoas() > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();

		voltas++;
	}
}