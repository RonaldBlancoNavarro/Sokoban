#ifndef NODO_H
#define NODO_H
#include <iostream>
using namespace std;

class Nodo {
private:
	string dato;
	Nodo* sig, * ant, * arriba, * abajo;
public:
	Nodo();
	Nodo(string);
	~Nodo();
	void setSig(Nodo*);
	void setAnt(Nodo*);
	void setArriba(Nodo*);
	void setAbajo(Nodo*);
	Nodo* getSig();
	Nodo* getAnt();
	Nodo* getArriba();
	Nodo* getAbajo();
	string getDato();
	void setDato(string);
};

#endif