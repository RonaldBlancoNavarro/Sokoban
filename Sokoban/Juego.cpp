#include "Juego.h"
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

Juego::Juego() {
    // inicializacion de elementos
    mat = new Matriz();
    clock = new Clock();
    tiempo = new Time();
    posicion = { 0,0 };
    solucion = false;
    ventana = new RenderWindow(VideoMode(900, 700), "SOKOBAN");
    imagen = new Texture();
    sprite = new Sprite();
    reinicio = new Sprite();
    imagen->loadFromFile("fondo.png", sf::IntRect(0, 0, 800, 600));
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
    

    btnNuevoJuego = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 200, 170, 80, &*font, "Nuevo Juego", 25, Color::Blue, Color::Green, Color::Red);
    btnCargarJuego = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 350, 170, 80, &*font, "Cargar Juego", 25, Color::Yellow, Color::Green, Color::Red);
    btnSalir = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 500, 170, 80, &*font, "Salir", 25, Color::Red, Color::Green, Color::Black);
    btnSolucionNivel = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 380, 170, 80, &*font, "Solucion Nivel", 25, Color::Cyan, Color::Green, Color::Black);
    btnRepeticion = new Boton(centro - titulo.getGlobalBounds().width / 3.f, 615, 170, 60, &*font, "Ver Repeticion", 25, Color::Yellow, Color::Green, Color::Red);
    btnSigNivel = new Boton(700, 615, 180, 60, &*font, "Siguiente Nivel", 25, Color::Yellow, Color::Green, Color::Red);
    btnGuardarPartida = new Boton(700, 615, 180, 60, &*font, "Guardar Partida", 25, Color::Yellow, Color::Green, Color::Red);
    btnMenuPrincipal = new Boton(50, 615, 180, 60, &*font, "Menu Principal", 25, Color::Yellow, Color::Green, Color::Red);
    btnReiniciarNivel = new Boton(800, 20, 60, 60, &*font, "", 25, Color::Transparent, Color::Cyan, Color::Transparent);
    this->estadoSubmenu = SBMN_INACTIVO;
    this->mapa = MAPA1;

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
    
    textureL = new Texture();
    textureL->loadFromFile("ladrillo.png");
    textureC1 = new Texture();
    textureC1->loadFromFile("caja1.png");
    textureP = new Texture();
    textureP->loadFromFile("personaje.png");
    reiniciar = new Texture();
    reiniciar->loadFromFile("Reiniciar.png");
    reinicio->setTexture(*reiniciar);
    reinicio->setScale((float)60 / reinicio->getTexture()->getSize().x, (float)60 / reinicio->getTexture()->getSize().y);
    pila = new stack<string>();

    contMov = 0;
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

        if (event.type == sf::Event::KeyPressed && estadoSubmenu == SBMN_PARTIDA) { // captura de accion en teclado para movimiento
            movientoPersonaje(event);
        }
        // get mouse position
        Vector2f posMouse = Vector2f(Mouse::getPosition(*ventana));

        // MENU Principal
        if (estadoSubmenu == SBMN_INACTIVO) {

            btnNuevoJuego->actualizarBoton(posMouse);
            btnCargarJuego->actualizarBoton(posMouse);
            btnSalir->actualizarBoton(posMouse);
        }

        // MENU Eleccion Nivel Nuevo Juego
        if (estadoSubmenu == SBMN_NUEVOJUEGO) {

            btnN1->actualizarBoton(posMouse);
            btnN2->actualizarBoton(posMouse);
            btnN3->actualizarBoton(posMouse);
            btnN4->actualizarBoton(posMouse);
            btnN5->actualizarBoton(posMouse);

            btnSiguiente->actualizarBoton(posMouse);
            btnAtras->actualizarBoton(posMouse);
        }

        // Partida
        if (estadoSubmenu == SBMN_PARTIDA) {
            btnAtras->actualizarBoton(posMouse);
            btnGuardarPartida->actualizarBoton(posMouse);
            btnReiniciarNivel->actualizarBoton(posMouse);
        }

        // MENU fin nivel
        if (estadoSubmenu == SBMN_SOLUCIONNIVEL){
            btnRepeticion->actualizarBoton(posMouse);
            btnSigNivel->actualizarBoton(posMouse);
            btnMenuPrincipal->actualizarBoton(posMouse);
        }
    }
}

void Juego::graficar()
{  
    ventana->draw(*sprite); //imagen
                                                                               // MENU Principal
    if (estadoSubmenu == SBMN_INACTIVO) { 
        ventana->draw(titulo);
        if (btnNuevoJuego->procesarBoton(&*ventana)) { 
            btnNuevoJuego->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_NUEVOJUEGO;
        }

        if (btnCargarJuego->procesarBoton(&*ventana)) {
            btnCargarJuego->setEstadoBoton(BTN_INACTIVO);
            nivelSolucion.clear();
            mat->limpiarMatriz();
            mat->cargarMatriz("CargarPartida");
            estadoSubmenu = SBMN_PARTIDA;
        }

        if (btnSalir->procesarBoton(&*ventana)) {
            btnSalir->setEstadoBoton(BTN_INACTIVO);
            ventana->close();
        }
    }
    if (estadoSubmenu == SBMN_NUEVOJUEGO) {                                                     //SELECCION DE NIVELES DE JUEGO
        descripcion.setString("Seleccione uno de los niveles, Para iniciar un Nuevo Juego");
        ventana->draw(descripcion);
        if (btnN1->procesarBoton(&*ventana)) { 
            mapa = MAPA1;
            nivel = "1";
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa1");
            btnN1->setEstadoBoton(BTN_INACTIVO);
        }

        if (btnN2->procesarBoton(&*ventana)) { 
            mapa = MAPA2;
            nivel = "2";
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa2");
            btnN2->setEstadoBoton(BTN_INACTIVO);
        }

        if (btnN3->procesarBoton(&*ventana)) { 
            mapa = MAPA3;
            nivel = "3";
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa3");
            btnN3->setEstadoBoton(BTN_INACTIVO);
        }

        if (btnN4->procesarBoton(&*ventana)) { 
            mapa = MAPA4;
            nivel = "4";
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa4");
            btnN4->setEstadoBoton(BTN_INACTIVO);           
        }

        if (btnN5->procesarBoton(&*ventana)) { 
            mapa = MAPA5;
            nivel = "5";
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa5");
            btnN5->setEstadoBoton(BTN_INACTIVO);
        }

        if (btnSiguiente->procesarBoton(&*ventana)) {          
            btnSiguiente->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_PARTIDA;
        }

        btnAtras->setBounds(Vector2f(150, 80));
        btnAtras->setPosicion(Vector2f(centro - titulo.getGlobalBounds().width / 3.f, 420));
        
        if (btnAtras->procesarBoton(&*ventana)) {          
            estadoSubmenu = SBMN_INACTIVO;
            btnAtras->setEstadoBoton(BTN_INACTIVO);
        }
    }

    if (estadoSubmenu == SBMN_PARTIDA) {  //PANTALLA EN EL MOMENTO DEL JUEGO
        procesarMapa();
        reinicio->setPosition(800, 20);
        ventana->draw(*reinicio);
        btnAtras->setBounds(Vector2f(120, 60));
        btnAtras->setPosicion(Vector2f((float)40, (float)615));
        if (btnAtras->procesarBoton(&*ventana)) {          
            btnAtras->setEstadoBoton(BTN_INACTIVO);
            nivelSolucion.clear();
            estadoSubmenu = SBMN_SOLUCIONNIVEL;
        }
        if (btnGuardarPartida->procesarBoton(&*ventana)) { 
            mat->guardarPartida("CargarPartida");
            btnGuardarPartida->setEstadoBoton(BTN_INACTIVO);         
        }
        if (btnReiniciarNivel->procesarBoton(&*ventana)) {
            mat->limpiarMatriz();
            nivelSolucion.clear();
            mat->cargarMatriz("Mapa" + nivel);
            btnGuardarPartida->setEstadoBoton(BTN_INACTIVO);
        }
    }
                                                // MENU DESPUES DE GANAR LA PARTIDA
    if (estadoSubmenu == SBMN_SOLUCIONNIVEL) {
        descripcion.setString("Usted a superado el nivel");
        descripcion.setPosition(centro - descripcion.getGlobalBounds().width / 2, 80);
        ventana->draw(descripcion);
        if (btnRepeticion->procesarBoton(&*ventana)) {
            mat->limpiarMatriz();
            mat->cargarMatriz("Mapa" + nivel);
            contMov = 0;
            if (!nivelSolucion.empty()) {
                solucion = true;
                estadoSubmenu = SBMN_SOLUCION;
                btnRepeticion->setEstadoBoton(BTN_INACTIVO);
            }           
        }
        if (btnSigNivel->procesarBoton(&*ventana)) {
            nivelSolucion.clear();
            mat->limpiarMatriz();
            int num = stoi(nivel);
            if (num != 5) {// para no avanzar a un nivel 6
                num++;
            }
            nivel = to_string(num);
            mat->cargarMatriz("Mapa" + nivel);           
            estadoSubmenu = SBMN_PARTIDA;
            btnSigNivel->setEstadoBoton(BTN_INACTIVO);
        }
        if (btnMenuPrincipal->procesarBoton(&*ventana)) {
            mat->limpiarMatriz();
            estadoSubmenu = SBMN_INACTIVO;
            btnAtras->setEstadoBoton(BTN_INACTIVO);
        }
    }
                                           //VISUALIZAR LA REPETICION DEL NIVEL JUGADO 
    if (estadoSubmenu == SBMN_SOLUCION) {
        procesarMapa();
        btnAtras->setBounds(Vector2f(120, 60));
        btnAtras->setPosicion(Vector2f((float)40, (float)615));
        if (btnAtras->procesarBoton(&*ventana)) {
            cout << "Atras" << endl;
            btnAtras->setEstadoBoton(BTN_INACTIVO);
            estadoSubmenu = SBMN_SOLUCIONNIVEL;
        }
    }
}

void Juego::graficarDato(string dato) {
    // pintado del dato guardado en respectiva posicion de matris (lista ortogonal)

    if (dato == "#") { // pared
        spritePos = new Sprite();
        spritePos->setTexture(*textureL);
        spritePos->setPosition(posicion);
        ventana->draw(*spritePos);
    }
    else if (dato == "$") {//caja
        spritePos = new Sprite();
        spritePos->setTexture(*textureC1);
        spritePos->setPosition(posicion);
        ventana->draw(*spritePos);
    }
    else if (dato == "@" || dato == "a") {// @ = jugador ... a = jugador sobre espacio para colocar una caja
        spritePos = new Sprite();
        spritePos->setTexture(*textureP);
        spritePos->setScale(50.f / spritePos->getTexture()->getSize().x, 50.f / spritePos->getTexture()->getSize().y); // tamaño deseado dividido entre tamaño actual
        spritePos->setPosition(posicion);
        ventana->draw(*spritePos);

        if (dato == "a") { // push en pila !
            pila->push(dato);
        }
    }
    else if (dato == "!") { // Caja ubicada en el espacio donde corresponde
        spritePos = new Sprite();
        spritePos->setTexture(*textureC1);
        spritePos->setPosition(posicion);
        spritePos->setColor(Color::Cyan);
        ventana->draw(*spritePos);

        // push en pila !
        pila->push(dato);
    }
    else if (dato == ".") { // espacio para colocar una caja
        sf::CircleShape shape(10.f);
        shape.setPosition(posicion.x + 15, posicion.y + 15);
        // set the shape color to green
        shape.setFillColor(sf::Color::Red);
        ventana->draw(shape);

        // push en pila .
        pila->push(dato);
    }

}

void Juego::procesarMapa() {  // recorrido de matriz para graficar sus datos
    Nodo* aux = NULL, * aux2 = NULL;
    aux = mat->getIni();
    float ancho = mapa * 50;
    posicion = { (float)(ventana->getSize().x/2) - ancho/2 , 50 };
    // recorrido de matriz fila a fila
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

    if (solucion) { // ejecucion solucion nivel
        solucionNivel();
    }

    if (finalizarNivel()) {  // salir de la pantalla de juego
        estadoSubmenu = SBMN_SOLUCIONNIVEL;
    }
}

void Juego::movientoPersonaje(Event event)
{    // captacion de movimiento, aceptacion o rechazo de este y guardado de este en nivelSolucion para repeticion

    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
        nivelSolucion.push_back('W');
        mat->verificarMovimiento('W');
    }
    if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
        nivelSolucion.push_back('S');
        mat->verificarMovimiento('S');
    }
    if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
        nivelSolucion.push_back('A');
        mat->verificarMovimiento('A');
    }
    if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
        nivelSolucion.push_back('D');
        mat->verificarMovimiento('D');
    }
}

bool Juego::finalizarNivel()
{// Inspeccion de pila para verificar nivel solucionado
    bool bandera = true;

    while (!pila->empty())
    {
        if (pila->top() == "." || pila->top() == "a") { // si hay espacio para caja no finaliza nivel

            bandera = false;
        }
        pila->pop();
    }

    return bandera;
}

void Juego::solucionNivel() {
    // recorrido de vector nivelSolucion para mostrar los movientos guardados en este durante la repeticion

    if (contMov < nivelSolucion.size()){
    
        *tiempo = clock->getElapsedTime();
   
        if (tiempo->asSeconds() > 0.3) { //Delay   -  Si este condicional se elimina, se ejecuta todo de una vez
            mat->verificarMovimiento(nivelSolucion[contMov]);
            //cout << nivelSolucion[contMov];
            contMov++;          
            clock->restart();
        }
    }
    else {
        solucion = false;
        contMov = 0;
    }
}