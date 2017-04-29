#ifndef PARQUE_H_
#define PARQUE_H_

class Parque {
    int numPessoas;

 public:
    Parque( int );
	virtual ~Parque();

    void setNumPessoas( int );
    int getNumPessoas();
    void sumNumPessoas( int );
};

#endif /* PARQUE_H_ */
