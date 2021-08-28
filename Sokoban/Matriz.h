#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include <fstream>
#include "Nodo.h"

using namespace std;
class Matriz
{
private:
	Nodo *ini, *fin,*finAb;
	string mapa;
public:
	Matriz();
	void setIni(Nodo*);
	void setFin(Nodo*);
	//void setIniAr(Nodo*);
	void setFinAb(Nodo*);
	void setMapa(string);
	Nodo* getIni();
	Nodo* getFin();
	//Nodo* getIniAr();
	Nodo* getFinAb();
	string getMapa();
	void cargarMatriz(string);
	void mostrar();
};
#endif