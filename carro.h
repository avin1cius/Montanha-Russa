#ifndef CARRO_H_
#define CARRO_H_

#include "parque.h"

class Carro {
    static int capacidade;
	int voltas;
    int maxVoltas;
	int numPassageiros;
	Parque &parque;

 public:
    Carro(Parque &p);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
	void esperaEsvaziar();
    void setMaxVoltas( int );
	int getNVoltas();
	Parque &getParque();
}

#endif /* CARRO_H_ */