#include "Nodo.h"

Nodo::Nodo(string dato) //:dato(dato)
{
	this->dato = dato;
	abajo = arriba = ant = sig = NULL;
}

Nodo::Nodo()
{
	dato = " ";
	abajo = arriba = ant = sig = NULL;
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

void Nodo::setDato(string dato)
{
	this->dato = dato;
}
