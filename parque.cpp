#include "parque.h"

Parque::Parque( int num ) {
	numPessoas = num;
}

Parque::~Parque() {
	// TODO Auto-generated destructor stub
}

void Parque::setNumPessoas( int num ) {
	numPessoas = num;
}

int Parque::getNumPessoas() {
	return numPessoas;
}
