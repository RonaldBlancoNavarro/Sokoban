#include "Juego.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Juego::Juego() {

    ventana = new RenderWindow(VideoMode(800, 600), "SOKOBAN");
    imagen = new Texture();
    sprite = new Sprite();
    imagen->loadFromFile("caja.png");
    sprite->setTexture(*imagen);

    font = new Font();
    font->loadFromFile("HU The Game.ttf");

    btn = new Boton(200, 200, 150, 80, &*font, "Prueba", 25, Color::Blue, Color::Green, Color::Red);
}

void Juego::mostrarVentana() // Loop principal
{
    while (ventana->isOpen())
    {
        dibujarVentana();
    }

}

void Juego::dibujarVentana()
{
    // area de eventos
    procesarEventos();

    //  Limpieza de pantalla
    ventana->clear(Color::White);

    //Area de dibujo de cosas    
    graficar();

    // mostar pantalla
    ventana->display();
}

void Juego::procesarEventos()
{
    sf::Event event;
    while (ventana->pollEvent(event)) // pollevent : escuchar evento 
    {
        if (event.type == sf::Event::Closed){
            ventana->close();
        }

        //switch (event.type)
        //{
        //case event.Closed:
        //{
        //    ventana->close();
        //    break;
        //}
        //default:
        //    break;
        //}

        // esto se podria mejorar 
        // get mouse position
        sf::Vector2i position = sf::Mouse::getPosition(*ventana);
        Vector2f vec = sf::Vector2f(position);
        btn->actualizarBoton(vec);
    }
}

void Juego::graficar()
{
    // lo mas seguro aqui hay que llamar al metodo que crea el menu

    ventana->draw(*sprite);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    ventana->draw(shape);

    if (btn->procesarBoton(&*ventana)) {
        cout << "Hola" << endl;
        btn->setEstadoBoton(BTN_INACTIVO);
    }
    
    Text texto;
    texto.setFont(*font);
    texto.setString("Texto");
    texto.setCharacterSize(40);
    texto.setPosition(400, 300);

    ventana->draw(texto);
}