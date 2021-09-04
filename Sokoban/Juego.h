#pragma once
#ifndef JUEGO_H
#define JUEGO_
#include <SFML/Graphics.hpp>
#include "Matriz.h"
#include "Boton.h"
#include <iostream>

using namespace sf;// este es para usar el SFML
using namespace std;

class Juego {
private:
	Matriz mat;
	RenderWindow* ventana;
	Texture* imagen;
	Sprite* sprite;
	Font* font;
	Text titulo;

	Boton* btnNuevoJuego;
	Boton* btnCargarJuego;
	Boton* btnSalir;
public:

	Juego();
	void mostrarVentana();
	void dibujarVentana();
	void procesarEventos();
	void graficar();


};

#endif