#ifndef CARRO_H_
#define CARRO_H_

#include "parque.h"
#include "thread.h"

class Carro: public Thread {
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
    virtual void run();
};

#endif /* CARRO_H_ */