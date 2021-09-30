#pragma once
#include <SFML/Graphics.hpp>
#include "Matriz.h"
#include "Boton.h"
#include <stack>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread> 
using namespace sf;// este es para usar el SFML
using namespace std;

enum estados_submenu { SBMN_INACTIVO = 0, SBMN_SUBMENU, SBMN_NUEVOJUEGO, SBMN_CARGARJUEGO, SBMN_SOLUCIONNIVEL, SBMN_SOLUCION, SBMN_PARTIDA};
enum mapa_seleccionado {MAPA1 = 10 , MAPA2 = 9, MAPA3 = 13, MAPA4 = 11, MAPA5 = 9};
class Juego {
private:
	Matriz *mat;
	Clock* clock;
	Time* tiempo;
	RenderWindow* ventana;
	Texture* imagen;
	Sprite* sprite;
	Font* font;
	Text titulo;
	float centro;
	bool solucion;
	Vector2f posicion;
	String nivel;
	Boton* btnNuevoJuego;
	Boton* btnCargarJuego;
	Boton* btnSolucionNivel;
	Boton* btnSalir;

	short unsigned estadoSubmenu; // unsigned es para no aceptar negativos
	short unsigned mapa;
	Text descripcion;
	Boton* btnSiguiente;
	Boton* btnAtras;
	Boton* btnN1;
	Boton* btnN2;
	Boton* btnN3;
	Boton* btnN4;
	Boton* btnN5;

	// texturas para graficar posiciones
	Texture* textureL;
	Texture* textureC1;
	Texture* textureP;
	Sprite* spritePos;

	stack<string>* pila;

	vector<char> nivelSolucion;
	int contMov;

public:

	Juego();
	void mostrarVentana();
	void dibujarVentana();
	void procesarEventos();
	void procesarMapa();
	void graficarDato(string);
	void graficar();
	void movientoPersonaje(Event event);
	void solucionNivel();
	bool finalizarNivel();
};
