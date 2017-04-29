#ifndef CARRO_H_
#define CARRO_H_

#include <iostream>
#include <thread>
#include <pthread.h>
#include "parque.h"
#include "atomico.h"

#define TEMP_VOLTA 5
#define MAX_NUM_VOLTAS 5

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
	void esperaEsvaziar();
    void sumNumPassageiros( int );
	int getNVoltas();
    int getCapacidade();
    int getNumPassageiros();
	Parque &getParque();
    void run();

	bool lock;

    int next, *turn;
};

#endif /* CARRO_H_ */
