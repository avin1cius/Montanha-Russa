#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "carro.h"
#include <cstdlib> //rand

class Passageiro {
    Carro &carro;
    Atomico &atomic;
    int id, randTime;

 public:
    Passageiro( Carro &c, Atomico &a );
    virtual ~Passageiro();
    void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
    void run( int );

    int nvoltas;
};

#endif /* PASSAGEIRO_H_ */
