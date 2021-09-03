#pragma once
#ifndef JUEGO_H
#define JUEGO_
#include <SFML/Graphics.hpp>
#include "Matriz.h"
#include <iostream>

using namespace sf;// este es para usar el SFML
using namespace std;

class Juego {
private:
	Matriz mat;
	RenderWindow *ventana; // con punteros por que sino jode cada rato
	Texture *imagen;
	Sprite *sprite;
public:

	Juego();
	void mostrarVentana();
	void dibujarVentana();
	void procesarEventos();
	void graficar();


};

#endif