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

    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    return 0;
}