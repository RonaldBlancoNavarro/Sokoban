#include "Juego.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Juego::Juego() {

    ventana = new RenderWindow(VideoMode(800, 600), "SOKOBAN");
    imagen = new Texture();
    sprite = new Sprite();
    imagen->loadFromFile("caja.png", sf::IntRect(0, 0, 800, 600));
    sprite->setTexture(*imagen);
    sprite->setScale(800.f / sprite->getTexture()->getSize().x, 600.f / sprite->getTexture()->getSize().y); // tamaño deseado dividido tamaño actual

    font = new Font();
    font->loadFromFile("HU The Game.ttf");

    titulo.setFont(*font);
    titulo.setString("-SOKOBAN-");
    titulo.setCharacterSize(50);
    titulo.setFillColor(Color::White);
    titulo.setPosition(400 - titulo.getGlobalBounds().width / 2.f, 50);


    btnNuevoJuego = new Boton(400 - titulo.getGlobalBounds().width / 3.f, 180, 150, 80, &*font, "Nuevo Juego", 25, Color::Blue, Color::Green, Color::Red);
    btnCargarJuego = new Boton(400 - titulo.getGlobalBounds().width / 3.f, 300, 150, 80, &*font, "Cargar Juego", 25, Color::Yellow, Color::Green, Color::Red);
    btnSalir = new Boton(400 - titulo.getGlobalBounds().width / 3.f, 420, 150, 80, &*font, "Salir", 25, Color::Red, Color::Green, Color::Black);

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
        if (event.type == sf::Event::Closed) {
            ventana->close();
        }

        // get mouse position
        Vector2f posMouse = sf::Vector2f(sf::Mouse::getPosition(*ventana));

        btnNuevoJuego->actualizarBoton(posMouse);
        btnCargarJuego->actualizarBoton(posMouse);
        btnSalir->actualizarBoton(posMouse);

    }
}

void Juego::graficar()
{
    // lo mas seguro aqui hay que llamar al metodo que crea el menu

    ventana->draw(*sprite); //imagen

    ventana->draw(titulo);

    if (btnNuevoJuego->procesarBoton(&*ventana)) { // Botones
        cout << "Nuevo Juego" << endl;
        btnNuevoJuego->setEstadoBoton(BTN_INACTIVO);
    }

    if (btnCargarJuego->procesarBoton(&*ventana)) {
        cout << "Cargar Juego" << endl;
        btnCargarJuego->setEstadoBoton(BTN_INACTIVO);
    }

    if (btnSalir->procesarBoton(&*ventana)) {
        cout << "Salir Juego" << endl;
        btnSalir->setEstadoBoton(BTN_INACTIVO);
    }

}