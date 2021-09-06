#include "Juego.h"
#include <SFML/Graphics.hpp>
using namespace sf;

Juego::Juego() {
    mat = new Matriz();   
    posicion = { 0,0 };
    ventana = new RenderWindow(VideoMode(900, 700), "SOKOBAN");
    imagen = new Texture();
    sprite = new Sprite();
    imagen->loadFromFile("caja.png", sf::IntRect(0, 0, 800, 600));
    sprite->setTexture(*imagen);
    sprite->setScale((float)ventana->getSize().x / sprite->getTexture()->getSize().x, (float)ventana->getSize().y / sprite->getTexture()->getSize().y); // tama�o deseado dividido tama�o actual

    Image img;
    img.loadFromFile("caja.png");
    ventana->setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

    font = new Font();
    font->loadFromFile("HU The Game.ttf");
    centro = ventana->getSize().x / 2;
    titulo.setFont(*font);
    titulo.setString("-SOKOBAN-");
    titulo.setCharacterSize(50);
    titulo.setFillColor(Color::White);
    titulo.setPosition(centro - titulo.getGlobalBounds().width / 2.f, 50);


    btnNuevoJuego = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 140, 170, 80, &*font, "Nuevo Juego", 25, Color::Blue, Color::Green, Color::Red);
    btnCargarJuego = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 260, 170, 80, &*font, "Cargar Juego", 25, Color::Yellow, Color::Green, Color::Red);
    btnSolucionNivel = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 380, 170, 80, &*font, "Solucion Nivel", 25, Color::Cyan, Color::Green, Color::Black);
    btnSalir = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 500, 170, 80, &*font, "Salir", 25, Color::Red, Color::Green, Color::Black);

    this->estadoSubmenu = SBMN_INACTIVO;

    descripcion.setFont(*font);
    descripcion.setString("Selecione uno de los siguientes niveles");
    descripcion.setCharacterSize(20);
    descripcion.setFillColor(Color::White);
    descripcion.setPosition(centro - titulo.getGlobalBounds().width, 80);


    btnN1 = new Boton(200, 180, 80, 80, &*font, "n1", 25, Color::Blue, Color::Green, Color::Red);
    btnN2 = new Boton(300, 180, 80, 80, &*font, "n2", 25, Color::Blue, Color::Green, Color::Red);
    btnN3 = new Boton(400, 180, 80, 80, &*font, "n3", 25, Color::Blue, Color::Green, Color::Red);
    btnN4 = new Boton(500, 180, 80, 80, &*font, "n4", 25, Color::Blue, Color::Green, Color::Red);
    btnN5 = new Boton(600, 180, 80, 80, &*font, "n5", 25, Color::Blue, Color::Green, Color::Red);


    btnSiguiente = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 300, 150, 80, &*font, "Siguiente", 25, Color::Yellow, Color::Green, Color::Red);
    btnAtras = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 420, 150, 80, &*font, "Atras", 25, Color::Red, Color::Green, Color::Black);
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

        //if (event.type == sf::Event::KeyPressed) {
        //    movientoPersonaje(event);
        //}

        // get mouse position
        Vector2f posMouse = Vector2f(Mouse::getPosition(*ventana));

        if (estadoSubmenu == SBMN_INACTIVO) {

            btnNuevoJuego->actualizarBoton(posMouse);
            btnCargarJuego->actualizarBoton(posMouse);
            btnSolucionNivel->actualizarBoton(posMouse);
            btnSalir->actualizarBoton(posMouse);
        }

        if (estadoSubmenu != SBMN_INACTIVO) {

            btnN1->actualizarBoton(posMouse);
            btnN2->actualizarBoton(posMouse);
            btnN3->actualizarBoton(posMouse);
            btnN4->actualizarBoton(posMouse);
            btnN5->actualizarBoton(posMouse);

            btnSiguiente->actualizarBoton(posMouse);
            btnAtras->actualizarBoton(posMouse);
        }

    }
}

void Juego::graficar()
{
    // lo mas seguro aqui hay que llamar al metodo que crea el menu
    ventana->draw(*sprite); //imagen

    if (estadoSubmenu == SBMN_INACTIVO) {

        ventana->draw(titulo);

        if (btnNuevoJuego->procesarBoton(&*ventana)) { // Botones
            cout << "Nuevo Juego" << endl;
            btnNuevoJuego->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_SUBMENU;
        }

        if (btnCargarJuego->procesarBoton(&*ventana)) {
            cout << "Cargar Juego" << endl;
            btnCargarJuego->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_CARGARJUEGO;
        }

        if (btnSolucionNivel->procesarBoton(&*ventana)) {
            cout << "Solucion Nivel" << endl;
            btnSolucionNivel->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_SOLUCIONNIVEL;
        }

        if (btnSalir->procesarBoton(&*ventana)) {
            cout << "Salir Juego" << endl;
            btnSalir->setEstadoBoton(BTN_INACTIVO);
            ventana->close();
        }

    }

    if (estadoSubmenu == SBMN_SUBMENU) {
        descripcion.setString("Seleccione uno de los niveles, Para iniciar un Nuevo Juego");
        ventana->draw(descripcion);
        if (btnN1->procesarBoton(&*ventana)) { // Botones
            cout << "n1" << endl;
            mapa = MAPA1;
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa1");
            btnN1->setEstadoBoton(BTN_INACTIVO);
            
        }

        if (btnN2->procesarBoton(&*ventana)) { // Botones
            cout << "n2" << endl;
            mapa = MAPA2;
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa2");
            btnN2->setEstadoBoton(BTN_INACTIVO);
            
        }

        if (btnN3->procesarBoton(&*ventana)) { // Botones
            cout << "n3" << endl;
            mapa = MAPA3;
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa3");
            btnN3->setEstadoBoton(BTN_INACTIVO);
            
        }

        if (btnN4->procesarBoton(&*ventana)) { // Botones
            cout << "n4" << endl; 
            mapa = MAPA4;
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa4");
            btnN4->setEstadoBoton(BTN_INACTIVO);           
        }

        if (btnN5->procesarBoton(&*ventana)) { // Botones
            cout << "n5" << endl;
            mapa = MAPA5;
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa5");
            btnN5->setEstadoBoton(BTN_INACTIVO);
        }

        if (btnSiguiente->procesarBoton(&*ventana)) { // Botones
            cout << "Siguiente" << endl;           
            btnSiguiente->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_PARTIDA;
        }
        btnAtras->setBounds(Vector2f(150, 80));
        btnAtras->setPosicion(Vector2f(centro - titulo.getGlobalBounds().width / 3.f, 420));
        if (btnAtras->procesarBoton(&*ventana)) {
            cout << "Atras" << endl;
            btnAtras->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_INACTIVO;
        }

    }

    if (estadoSubmenu == SBMN_NUEVOJUEGO) {
        descripcion.setString("Seleccione uno de los niveles, Para iniciar un Nuevo Juego");
        ventana->draw(descripcion);
    }
    if (estadoSubmenu == SBMN_CARGARJUEGO) {
        descripcion.setString("Seleccione uno de los niveles, Para Cargar un Juego Anterior");
        ventana->draw(descripcion);
    }
    if (estadoSubmenu == SBMN_SOLUCIONNIVEL) {
        descripcion.setString("Seleccione uno de los niveles, Para Visualizar su Solucion");
        ventana->draw(descripcion);
    }
    if (estadoSubmenu == SBMN_PARTIDA) {
        procesarMapa();
        btnAtras->setBounds(Vector2f(120, 60));
        btnAtras->setPosicion(Vector2f((float)40, (float)615));
        if (btnAtras->procesarBoton(&*ventana)) {
            cout << "Atras" << endl;
            btnAtras->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_SUBMENU;
        }
    }
    //procesarMapa();
}
void Juego::graficarDato(string dato) {
    Texture* texture;
    Sprite* sprite;
    if (dato == "#") {
        texture = new Texture();
        sprite = new Sprite();
        texture->loadFromFile("ladrillo.png");
        sprite->setTexture(*texture);
        sprite->setPosition(posicion);
        ventana->draw(*sprite);
    }
    else if (dato == "$") {
        texture = new Texture();
        sprite = new Sprite();
        texture->loadFromFile("caja1.png");
        sprite->setTexture(*texture);
        sprite->setPosition(posicion);
        ventana->draw(*sprite);
    }
    else if(dato == "@") {
        texture = new Texture();
        sprite = new Sprite();
        texture->loadFromFile("personaje.png");
        sprite->setTexture(*texture);
        sprite->setPosition(posicion);
        ventana->draw(*sprite);
    }

}
void Juego::procesarMapa() {  
    Nodo* aux = NULL, * aux2 = NULL;
    aux = mat->getIni();
    float ancho = mapa * 50;
    posicion = { (float)(ventana->getSize().x/2) - ancho/2 , 50 };
    while (aux != NULL) {
        aux2 = aux;
        while (aux2 != NULL) {
            graficarDato(aux2->getDato());
            posicion.x += 50;
            aux2 = aux2->getSig();
        }
        posicion.x = (float)(ventana->getSize().x / 2) - ancho / 2;
        posicion.y += 50;
        aux = aux->getAbajo();
    }
}

void Juego::movientoPersonaje(Event event)
{
    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
        mat->verificarMovimiento('W');
    }
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
        mat->verificarMovimiento('S');
    }
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
        mat->verificarMovimiento('A');
    }
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
        mat->verificarMovimiento('D');
    }
}