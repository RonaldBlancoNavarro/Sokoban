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

				// comprobacion si el caracter es  diferente de un salto de linea
				if (nodo->getDato()[0] != 10) 
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