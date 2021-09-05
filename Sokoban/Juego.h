#pragma once
#include <SFML/Graphics.hpp>
#include "Matriz.h"
#include "Boton.h"
#include <iostream>
#include <list>
using namespace sf;// este es para usar el SFML
using namespace std;

enum estados_submenu { SBMN_INACTIVO = 0, SBMN_NUEVOJUEGO, SBMN_CARGARJUEGO, SBMN_SOLUCIONNIVEL };

class Juego {
private:
	Matriz *mat;
	RenderWindow* ventana;
	Texture* imagen;
	Sprite* sprite;
	Font* font;
	Text titulo;
	Vector2f posicion;
	Boton* btnNuevoJuego;
	Boton* btnCargarJuego;
	Boton* btnSolucionNivel;
	Boton* btnSalir;

	short unsigned estadoSubmenu; // unsigned es para no aceptar negativos

	Text descripcion;
	Boton* btnSiguiente;
	Boton* btnAtras;
	Boton* btnN1;
	Boton* btnN2;
	Boton* btnN3;
	Boton* btnN4;
	Boton* btnN5;


public:

	Juego();
	void mostrarVentana();
	void dibujarVentana();
	void procesarEventos();
	void procesarMapa();
	void graficarMapa(string);
	void graficar();
};
