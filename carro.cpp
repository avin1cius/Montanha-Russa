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
    while ( numPassageiros != capacidade );
    std::cerr << "Encheu" << std::endl;
    lock = true;
}

void Carro::daUmaVolta() {
    std::cerr << voltas << "ª volta iniciada" << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds( TEMP_VOLTA )); //dorme alguns segundos
    std::cerr << voltas << "ª volta finalizada" << std::endl;
    lock = false;
}

void Carro::esperaEsvaziar() {
    while ( numPassageiros );
    std::cerr<<"Esvaziou"<<std::endl;
}

void Carro::sumNumPassageiros( int num) {
    numPassageiros += num;
    std::cerr << "numPass " << numPassageiros << std::endl;
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
	while ( next != MAX_NUM_VOLTAS * getCapacidade() + 1 ) {
		esperaEncher();  //aguarda Passageiro::entraNoCarro()

		daUmaVolta();

		esperaEsvaziar(); //aguarda Passageiro::saiDoCarro() zerar numPassageiros

		++voltas;
		++next;
	}

	while ( parque.getNumPessoas());
	std::cerr << "Parque fechou" << std::endl;
}
