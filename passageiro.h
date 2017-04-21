#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "carro.h"
#include <cstdlib> //rand

class Passageiro {
    Carro &carro;
    size_t id;

 public:
    Passageiro(Carro &c);
    virtual ~Passageiro();
    void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
    void run( int );
};

#endif /* PASSAGEIRO_H_ */