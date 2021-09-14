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
	bool primeraFila = true;
	bool primeraColumna = false;
	file.open(".\\Mapas\\" + mapa + ".txt");

	if (!file) {
		cout << "No se encontro el archivo" << endl;
	}
	else {
		Nodo* nodo, *aux = NULL;
		nodo = new Nodo();
		aux = new Nodo();
		
		caracter = file.get();
		caracter = file.get();
		while (!file.eof()) {
			caracter = file.get();
			nodo = new Nodo(caracter);
			if (ini == NULL) { // coloca el primer nodo
				ini = nodo;
				fin = nodo;
				finAb = nodo;				
				ini->setSig(NULL);
				ini->setAnt(NULL);
				ini->setAbajo(NULL);
				ini->setArriba(NULL);
			}
			else
			{
				if (nodo->getDato()[0] != 10 && primeraFila) {
					fin->setSig(nodo);
					nodo->setAnt(fin);
					nodo->setArriba(NULL);
					nodo->setAbajo(NULL);
					fin = nodo;
				}
				else if (nodo->getDato()[0] == 10 && primeraFila) {
					fin->setSig(nodo);
					nodo->setAnt(fin);
					nodo->setArriba(NULL);
					nodo->setAbajo(NULL);
					nodo->setSig(NULL);
					aux = finAb;
					primeraColumna = true;
					primeraFila = false;
				}
				else if (primeraColumna) {
					aux->setAbajo(nodo);
					nodo->setArriba(aux);
					nodo->setAnt(NULL);
					nodo->setSig(NULL);
					fin = nodo;
					finAb = nodo;
					aux = aux->getSig();
					primeraColumna = false;
				}
				else if (nodo->getDato()[0] == 10  && !primeraFila) {
					fin->setSig(nodo);
					nodo->setAnt(fin);
					nodo->setArriba(aux);
					nodo->setAbajo(NULL);
					nodo->setSig(NULL);
					if (aux != NULL) {
						aux->setAbajo(nodo);
					}
					aux = finAb;
					primeraColumna = true;
				}
				else if (nodo->getDato()[0] != 10 && !primeraFila && !primeraColumna) {					
					fin->setSig(nodo);
					nodo->setAnt(fin);
					nodo->setSig(NULL);
					nodo->setArriba(aux);
					nodo->setAbajo(NULL);
					fin = nodo;
					if (aux != NULL) {
						aux->setAbajo(nodo);
						aux = aux->getSig();
					}
					else {
						aux = NULL;
					}					
				}
			}
		}
		file.close();
	}
}

void Matriz::limpiarMatriz() {
	ini = NULL;
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
			//cout << endl;
			//cout << aux->getDato();
			aux = aux->getAbajo();
		}
	}
}

bool Matriz::verificarMovimiento(char movimiento)
{ // metodo que decide aplicar el movimiento de caracteres en la matriz
//y aplicar dicho movimiento en caso de ser necesario
	Nodo* aux = NULL, * aux2 = NULL;
	aux = ini;

	while (aux != NULL) {
		aux2 = aux;
		while (aux2 != NULL) {
			if (aux2->getDato() == "@" || aux2->getDato() == "a") {
				bool mover = false;

				switch (movimiento)
				{
				case 'W': {

						if (aux2->getArriba()->getDato() == "@" || aux2->getArriba()->getDato() == "a" || aux2->getArriba()->getDato() == "#" ) {
							// si es un jugador,pared
							mover = false;
						}
						else {
							if (aux2->getArriba()->getDato() == " " || aux2->getArriba()->getDato() == ".") {
								//si es espacio en blanco, espacio para colocar una caja
								mover = true;
							}
							else {
								if (aux2->getArriba()->getDato() == "$" || aux2->getArriba()->getDato() == "!") {
									//si es una caja,Caja ubicada en el espacio donde corresponde
									if (aux2->getArriba()->getArriba() != NULL) {

										if (aux2->getArriba()->getArriba()->getDato() == " " || aux2->getArriba()->getArriba()->getDato() == ".") {
											//si es espacio en blanco, espacio para colocar una caja
											mover = true;
										}
										else {
											mover = false;
										}

									}
									else { mover = false; }
								}
							}
						}


						// seccion para aplicar cambios
						if (mover) {

							if (aux2->getArriba()->getDato() != "$" && aux2->getArriba()->getDato() != "!") { // si arriba diferente de caja


								if (aux2->getArriba()->getDato() == " ") {// si arriba igual a espacio en blanco
									aux2->getArriba()->setDato("@");
								}
								else {
									//si habia espacio para colocar caja
									aux2->getArriba()->setDato("a");
								}

							}
							else {
								if (aux2->getArriba()->getArriba()->getDato() == ".") {
									// si arriba de la caja  habia espacio para colocar caja
									aux2->getArriba()->getArriba()->setDato("!");
								}
								else{
									aux2->getArriba()->getArriba()->setDato("$");
								}

								if (aux2->getArriba()->getDato() == "$") {
									// si donde la caja estaba NO existia punto para colocar una caja
									aux2->getArriba()->setDato("@");
								}
								else { // si la caja estaba ubicada en el espacio donde corresponde
									aux2->getArriba()->setDato("a");
								}

							}

							// terminar de mover al personaje de la posicion donde estaba
							if (aux2->getDato() == "@") {// si es @ debajo habia un espacio en blanco
								aux2->setDato(" ");
							}
							else if (aux2->getDato() == "a") {// si es un a habia espacio para colocar caja
								aux2->setDato(".");
							}

							return true;
						}
							return false;
					break;
				}
				case 'S': {

					if (aux2->getAbajo()->getDato() == "@" || aux2->getAbajo()->getDato() == "a" || aux2->getAbajo()->getDato() == "#") {
						// si es un jugador,pared
						mover = false;
					}
					else {
						if (aux2->getAbajo()->getDato() == " " || aux2->getAbajo()->getDato() == ".") {
							//si es espacio en blanco, espacio para colocar una caja
							mover = true;
						}
						else {
							if (aux2->getAbajo()->getDato() == "$" || aux2->getAbajo()->getDato() == "!") {
								//si es una caja,Caja ubicada en el espacio donde corresponde
								if (aux2->getAbajo()->getAbajo() != NULL) {

									if (aux2->getAbajo()->getAbajo()->getDato() == " " || aux2->getAbajo()->getAbajo()->getDato() == ".") {
										//si es espacio en blanco, espacio para colocar una caja
										mover = true;
									}
									else {
										mover = false;
									}

								}
								else { mover = false; }
							}
						}
					}


					// seccion para aplicar cambios
					if (mover) {

						if (aux2->getAbajo()->getDato() != "$" && aux2->getAbajo()->getDato() != "!") { // si Abajo diferente de caja


							if (aux2->getAbajo()->getDato() == " ") {// si Abajo igual a espacio en blanco
								aux2->getAbajo()->setDato("@");
							}
							else {
								//si habia espacio para colocar caja
								aux2->getAbajo()->setDato("a");
							}

						}
						else {
							if (aux2->getAbajo()->getAbajo()->getDato() == ".") {
								// si Abajo de la caja  habia espacio para colocar caja
								aux2->getAbajo()->getAbajo()->setDato("!");
							}
							else {
								aux2->getAbajo()->getAbajo()->setDato("$");
							}

							if (aux2->getAbajo()->getDato() == "$") {
								// si donde la caja estaba NO existia punto para colocar una caja
								aux2->getAbajo()->setDato("@");
							}
							else { // si la caja estaba ubicada en el espacio donde corresponde
								aux2->getAbajo()->setDato("a");
							}

						}

						// terminar de mover al personaje de la posicion donde estaba
						if (aux2->getDato() == "@") {// si es @ debajo habia un espacio en blanco
							aux2->setDato(" ");
						}
						else if (aux2->getDato() == "a") {// si es un a habia espacio para colocar caja
							aux2->setDato(".");
						}

						return true;
					}
					return false;
					break;
				}
				case 'A': {

					if (aux2->getAnt()->getDato() == "@" || aux2->getAnt()->getDato() == "a" || aux2->getAnt()->getDato() == "#") {
						// si es un jugador,pared
						mover = false;
					}
					else {
						if (aux2->getAnt()->getDato() == " " || aux2->getAnt()->getDato() == ".") {
							//si es espacio en blanco, espacio para colocar una caja
							mover = true;
						}
						else {
							if (aux2->getAnt()->getDato() == "$" || aux2->getAnt()->getDato() == "!") {
								//si es una caja,Caja ubicada en el espacio donde corresponde
								if (aux2->getAnt()->getAnt() != NULL) {

									if (aux2->getAnt()->getAnt()->getDato() == " " || aux2->getAnt()->getAnt()->getDato() == ".") {
										//si es espacio en blanco, espacio para colocar una caja
										mover = true;
									}
									else {
										mover = false;
									}

								}
								else { mover = false; }
							}
						}
					}


					// seccion para aplicar cambios
					if (mover) {

						if (aux2->getAnt()->getDato() != "$" && aux2->getAnt()->getDato() != "!") { // si Ant diferente de caja


							if (aux2->getAnt()->getDato() == " ") {// si Ant igual a espacio en blanco
								aux2->getAnt()->setDato("@");
							}
							else {
								//si habia espacio para colocar caja
								aux2->getAnt()->setDato("a");
							}

						}
						else {
							if (aux2->getAnt()->getAnt()->getDato() == ".") {
								// si Ant de la caja  habia espacio para colocar caja
								aux2->getAnt()->getAnt()->setDato("!");
							}
							else {
								aux2->getAnt()->getAnt()->setDato("$");
							}

							if (aux2->getAnt()->getDato() == "$") {
								// si donde la caja estaba NO existia punto para colocar una caja
								aux2->getAnt()->setDato("@");
							}
							else { // si la caja estaba ubicada en el espacio donde corresponde
								aux2->getAnt()->setDato("a");
							}

						}

						// terminar de mover al personaje de la posicion donde estaba
						if (aux2->getDato() == "@") {// si es @ debajo habia un espacio en blanco
							aux2->setDato(" ");
						}
						else if (aux2->getDato() == "a") {// si es un a habia espacio para colocar caja
							aux2->setDato(".");
						}

						return true;
					}
					return false;
					break;
				}
				case 'D': {

					if (aux2->getSig()->getDato() == "@" || aux2->getSig()->getDato() == "a" || aux2->getSig()->getDato() == "#") {
						// si es un jugador,pared
						mover = false;
					}
					else {
						if (aux2->getSig()->getDato() == " " || aux2->getSig()->getDato() == ".") {
							//si es espacio en blanco, espacio para colocar una caja
							mover = true;
						}
						else {
							if (aux2->getSig()->getDato() == "$" || aux2->getSig()->getDato() == "!") {
								//si es una caja,Caja ubicada en el espacio donde corresponde
								if (aux2->getSig()->getSig() != NULL) {

									if (aux2->getSig()->getSig()->getDato() == " " || aux2->getSig()->getSig()->getDato() == ".") {
										//si es espacio en blanco, espacio para colocar una caja
										mover = true;
									}
									else {
										mover = false;
									}

								}
								else { mover = false; }
							}
						}
					}


					// seccion para aplicar cambios
					if (mover) {

						if (aux2->getSig()->getDato() != "$" && aux2->getSig()->getDato() != "!") { // si Sig diferente de caja


							if (aux2->getSig()->getDato() == " ") {// si Sig igual a espacio en blanco
								aux2->getSig()->setDato("@");
							}
							else {
								//si habia espacio para colocar caja
								aux2->getSig()->setDato("a");
							}

						}
						else {
							if (aux2->getSig()->getSig()->getDato() == ".") {
								// si Sig de la caja  habia espacio para colocar caja
								aux2->getSig()->getSig()->setDato("!");
							}
							else {
								aux2->getSig()->getSig()->setDato("$");
							}

							if (aux2->getSig()->getDato() == "$") {
								// si donde la caja estaba NO existia punto para colocar una caja
								aux2->getSig()->setDato("@");
							}
							else { // si la caja estaba ubicada en el espacio donde corresponde
								aux2->getSig()->setDato("a");
							}

						}

						// terminar de mover al personaje de la posicion donde estaba
						if (aux2->getDato() == "@") {// si es @ debajo habia un espacio en blanco
							aux2->setDato(" ");
						}
						else if (aux2->getDato() == "a") {// si es un a habia espacio para colocar caja
							aux2->setDato(".");
						}

						return true;
					}
					return false;
					break;
				}
				default:
					return false;
					break;
				}
			}

			aux2 = aux2->getSig();
		}
		aux = aux->getAbajo();
	}


	return false;
}

