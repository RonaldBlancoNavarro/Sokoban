#include "Nodo.h"

Nodo::Nodo(string dato) :
	dato(dato)
{
}

Nodo::Nodo()
{
}

Nodo::~Nodo()
{
}

void Nodo::setSig(Nodo* sig) {
	this->sig = sig;
}
void Nodo::setAnt(Nodo* ant) {
	this->ant = ant;
}
void Nodo::setArriba(Nodo* arriba) {
	this->arriba = arriba;
}
void Nodo::setAbajo(Nodo* abajo) {
	this->abajo = abajo;
}

Nodo* Nodo::getSig() {
	return sig;
}
Nodo* Nodo::getAnt() {
	return ant;
}
Nodo* Nodo::getArriba() {
	return arriba;
}
Nodo* Nodo::getAbajo() {
	return abajo;
}

string Nodo::getDato() {
	return dato;
}
