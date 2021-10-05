#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include <fstream>
#include "Nodo.h"
#include <vector>

using namespace std;
class Matriz
{
private:
	Nodo *ini, *fin,*finAb;  // ini = inicio matriz . fin = posicicion final actual matriz . finAb = finAbajo primer posicion ultima fila
	string mapa; // nombre documento con mapa nivel
public:
	Matriz();
	void setIni(Nodo*);
	void setFin(Nodo*);
	void setFinAb(Nodo*);
	void setMapa(string);
	Nodo* getIni();
	Nodo* getFin();
	Nodo* getFinAb();
	string getMapa();
	void cargarMatriz(string);
	void limpiarMatriz();
	void mostrar();
	bool verificarMovimiento(char movimiento);
	void guardarPartida(string);
	void guardarMovimientos(vector<char>);
};
#endif