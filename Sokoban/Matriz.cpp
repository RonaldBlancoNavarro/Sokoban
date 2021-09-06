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
				// comprobacion si el caracter es  diferente de un salto de linea
			/*	if (nodo->getDato()[0] != 10)
				{

					//Colocacion del siguiente nodo despues de fin : conexion horizontal
					fin->setSig(nodo);
					nodo->setAnt(fin);
					nodo->setSig(NULL);
					nodo->setAbajo(NULL);


					if (fin->getArriba() == NULL || fin->getArriba()->getSig() == NULL) {
						// si no hay nodo arriba en fin ->NULL
						// si en fin->arriba->sig es NULL-> NULL
						nodo->setArriba(NULL);
					}
					else {
						// realizamos conexion vertical
						nodo->setArriba(fin->getArriba()->getSig());
						fin->getArriba()->getSig()->setAbajo(nodo);
					}

					fin = nodo;// avanza fin a la siguiente posicion
				}
				else // si el caracter es un salto de linea -revisar- puede ser que este insertando el salto de linea al inicio de una nueva fila
				{
					aux = ini;
					// recorrer la lista para abajo en la primer columna con aux
					while (aux != NULL) {
						// si el siguiente  no es nulo se avanza
						if (aux->getAbajo() != NULL) {
							aux = aux->getAbajo();
						}
						else {
							// si el siguiente es nulo se detiene el avanze
							// encontrando el nodo sobre el que se va a insertar debajo el nuevo nodo
							break;
						}
					}

					//insertar el nuevo nodo haciendo las conexiones

					nodo->setAnt(NULL);// conexioneshorizontales
					nodo->setSig(NULL);
					aux->setAbajo(nodo);// conexiones verticales
					nodo->setArriba(aux);
					nodo->setAbajo(NULL);

					fin = nodo;// avanza fin a la siguiente posicion que seria el inicio de una nueva fila
				}

			}*/
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

void Matriz::verificarMovimiento(char movimiento)
{ // metodo que decide aplicar el movimiento de caracteres en la matriz
//y aplicar dicho movimiento en caso de ser necesario
	Nodo* aux = NULL, * aux2 = NULL;
	aux = ini;

	while (aux != NULL) {
		aux2 = aux;
		while (aux2 != NULL) {
			if (aux2->getDato() == "@") {
				bool mover = false;

				switch (movimiento)
				{
				case 'W': {
					if (aux2->getArriba() != NULL) {

						if (aux2->getArriba()->getDato() == "@" || aux2->getArriba()->getDato() == "#" || aux2->getArriba()->getDato() == "!") {
							// si es un jugador,pared,Caja ubicada en el espacio donde corresponde
							mover = false;
						}
						else {
							if (aux2->getArriba()->getDato() == " " || aux2->getArriba()->getDato() == ".") {
								//si es espacio en blanco, espacio para colocar una caja
								mover = true;
							}
							else {
								if (aux2->getArriba()->getDato() == "$") {
									//si es una caja
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
							// aqui se complica la situacion pues mover el 
							// personaje y en caso de ser necesario la caja,
							// tambien hay que considerar que estos podian tapar:
							//espacio en blanco , espacio para colocar una caja
							// y estos deben de volver a como estaban en caso de ser necesario
						}
					}
					break;
				}
				case 'S': {
					break;
				}
				case 'A': {
					break;
				}
				case 'D': {
					break;
				}
				default:
					break;
				}
			}

			aux2 = aux2->getSig();
		}
		aux = aux->getAbajo();
	}

}

