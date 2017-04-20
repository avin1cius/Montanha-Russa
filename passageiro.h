#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "carro.h"
#include "thread.h"

class Passageiro: public Thread {
    Carro &carro;

 public:
    Passageiro(Carro &c);
    virtual ~Passageiro();
    void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
};

#endif /* PASSAGEIRO_H_ */