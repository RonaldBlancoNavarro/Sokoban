#include <SFML/Graphics.hpp>
#include<iostream>
#include "Matriz.h"
#include "Juego.h"

/*
    PROYECTO 1 ESTRUCTURAS DE DATOS
   - SOKOBAN -
    CICLO 2 - 2021
    ESTUDIANTES:
    KEINER GODINEZ AGUILAR 116980821
    RONALD BLANCO NAVARRO 117580543
*/

int main()
{
    // Inicio Juego
    Juego* game = new Juego();
    game->mostrarVentana();
    return 0;
}