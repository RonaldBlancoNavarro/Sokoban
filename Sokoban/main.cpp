#include <SFML/Graphics.hpp>
#include<iostream>
#include "Matriz.h"
#include "Juego.h"
int main()
{
    Juego *game = new Juego();
    game->mostrarVentana();

    //Matriz mat;
    //mat.cargarMatriz("Mapa1");
    //mat.mostrar();

    return 0;
}