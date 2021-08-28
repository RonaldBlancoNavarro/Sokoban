#include "Matriz.h"

Matriz::Matriz()
{
	ini = fin = finAb = NULL;
}

void Matriz::setIni(Nodo* ini) {
	this->ini = ini;
}

void Matriz::setFin(Nodo* fin) {
	this->fin = fin;
}
/*void Matriz::setIniAr(Nodo* iniAr) {
	this->iniAr = iniAr;
}*/

void Matriz::setFinAb(Nodo* finAb) {
	this->finAb = finAb;
}

void Matriz::setMapa(string mapa) {
	this->mapa = mapa;
}

Nodo* Matriz::getIni() {
	return ini;
}
/*Nodo* Matriz::getIniAr() {
	return iniAr;
}*/

Nodo* Matriz::getFin() {
	return fin;
}

Nodo* Matriz::getFinAb() {
	return finAb;
}
string Matriz::getMapa() {
	return mapa;
}

void Matriz::cargarMatriz(string mapa) {
	ifstream file;
	string caracter;
	file.open(".\\Mapas\\" + mapa + ".txt");

	if (!file) {
		cout << "No se encontro el archivo" << endl;
	}
	else {
		Nodo* nodo;
		caracter = file.get();
		caracter = file.get();
		while (!file.eof()) {
			caracter = file.get();
			nodo = new Nodo(caracter);
			if (ini == NULL) {
				ini = nodo;
				fin = nodo;
				finAb = nodo;				
				ini->setSig(NULL);
				ini->setAnt(NULL);
				ini->setAbajo(NULL);
				ini->setArriba(NULL);
			}
			else {
				fin->setSig(nodo);
				nodo->setAnt(fin);
				fin = nodo;
			}
		}
		file.close();
	}
}

void Matriz::mostrar() {
	if (ini != NULL) {
		Nodo *aux = ini,*aux2;
		while (aux != NULL) {
			aux2 = aux;
			while (aux2 != NULL) {
				cout << aux2->getDato();
				aux2 = aux2->getSig();
			}
			aux = aux->getAbajo();
		}
	}
}