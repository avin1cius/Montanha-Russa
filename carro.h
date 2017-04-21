#ifndef CARRO_H_
#define CARRO_H_

#include "parque.h"
#include <thread>
#include <atomic>

class Carro {
    static int capacidade;
	int voltas;
	int numPassageiros;
    bool fimVolta;
	Parque &parque;
    size_t id;

 public:
    Carro(Parque &p);
	virtual ~Carro();
	void esperaEncher();
	void daUmaVolta();
    void sumNumPassageiros( int );
	void esperaEsvaziar();
	int getNVoltas();
    int getCapacidade();
    int getNumPassageiros();
	Parque &getParque();
    void run();

	bool lock;
    
    int next, *turn;
};

#endif /* CARRO_H_ */