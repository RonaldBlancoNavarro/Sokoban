#include "Juego.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Juego::Juego() {

    ventana.create(VideoMode(800, 600), "SOKOBAN");

}

void Juego::mostrarVentana() // Loop principal
{
    while (ventana.isOpen())
    {
        dibujarVentana();
    }

}

void Juego::dibujarVentana()
{
    // area de eventos
    procesarEventos();

    //  Limpieza de pantalla
    ventana.clear(Color::White);

    //Area de dibujo de cosas
    graficar();

    // mostar pantalla
    ventana.display();
}

void Juego::procesarEventos()
{
    sf::Event event;
    while (ventana.pollEvent(event)) // pollevent : escuchar evento 
    {
        //if (event.type == sf::Event::Closed)
        //    ventana.close();

        switch (event.type)
        {
        case event.Closed:
        {
            ventana.close();
            break;
        }
        default:
            break;
        }
    }
}

void Juego::graficar()
{
    // lo mas seguro aqui hay que llamar al metodo que crea el menu

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    ventana.draw(shape);


    //Texture textura;
    //textura.loadFromFile("caja.png");
    //Sprite sprt;
    //sprt.setTexture(textura);
    //sprt.setPosition(100, 100);
    //ventana.draw(sprt);

    //if (!texture.loadFromFile("caja.png", sf::IntRect(10, 10, 32, 32)))
    //{
    //    // error...
    //}

   // Font fuente;
   // fuente.loadFromFile("HU The Game.ttf"); 
   // Text texto;
   // texto.setFont(fuente);
   // texto.setString("Prueba");
   // texto.setPosition(400, 300);
   //// texto.setColor(Color::Black);

   // ventana.draw(texto);
}