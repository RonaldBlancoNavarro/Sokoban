#include <SFML/Graphics.hpp>
#include<iostream>
#include "Matriz.h"
#include "Juego.h"
int main()
{
    //Matriz mat;
    //mat.cargarMatriz("Mapa2");
    //mat.mostrar();
    Juego* game = new Juego();
    game->mostrarVentana();
    return 0;
}