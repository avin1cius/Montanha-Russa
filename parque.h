#ifndef PARQUE_H_
#define PARQUE_H_

class Parque {
    //int numPessoas;

 public:
    int numPessoas;
    Parque( int );
	virtual ~Parque();

    void setNumPessoas( int );
    int getNumPessoas();
};

#endif /* PARQUE_H_ */
