//
// Created by senpai on 7/24/19.
//

#include "AdministradorDeSonido.hpp"

AdministradorDeSonido::AdministradorDeSonido()
{
    //cargamos los .wav
    bufferFuego.loadFromFile("../sonidos/fuego1.wav");
    bufferCaerEnFuego.loadFromFile("../sonidos/caerEnFuego.wav");
    bufferCaerEnAgua.loadFromFile("../sonidos/caerEnAgua.wav");
    bufferBrinco.loadFromFile("../sonidos/brinco.wav");
    bufferAlcanzarMeta.loadFromFile("../sonidos/metaAlcanzada.wav");

    sonidoFuego1.setBuffer(bufferFuego);
    sonidoFuego2.setBuffer(bufferFuego);
    sonidoFuego3.setBuffer(bufferFuego);

    sonidoCaerEnFuego.setBuffer(bufferCaerEnFuego);
    sonidoCaerEnAgua.setBuffer(bufferCaerEnAgua);
    sonidoBrinco.setBuffer(bufferBrinco);
    sonidoAlcanzarMeta.setBuffer(bufferAlcanzarMeta);

    //distancia minima para empezar atenuación del sonido
    //en pixeles
    float distanciaMin = 150;

    //la atenuación que exites cuando el jugador se va alejando del
    //emisor
    //el calculo de esta atenuación se hizo mediante tanteo
    float atenuacion = 15;

    //asigmanos las atenuaciones
    sonidoFuego1.setAttenuation(atenuacion);
    sonidoFuego2.setAttenuation(atenuacion);
    sonidoFuego3.setAttenuation(atenuacion);

    //asignamos la distancia minima
    sonidoFuego1.setMinDistance(distanciaMin);
    sonidoFuego2.setMinDistance(distanciaMin);
    sonidoFuego3.setMinDistance(distanciaMin);

    //ciclamos el sonido del fuego
    sonidoFuego1.setLoop(true);
    sonidoFuego2.setLoop(true);
    sonidoFuego3.setLoop(true);
}

void AdministradorDeSonido::reproducirFuego(sf::Vector2f lugarEmisor, sf::Vector2f lugarReceptor)
{
    //el sonido se representa en 3D
    sf::Listener::setPosition(lugarReceptor.x,lugarReceptor.y,0.0f);

    switch (siguienteSonido)
    {
        case 1:
            sonidoFuego1.setPosition(lugarEmisor.x,lugarEmisor.y,0.0f);

            if(sonidoFuego1.getStatus() == sf::Sound::Status::Stopped)
                sonidoFuego1.play();
            break;

        case 2:
            sonidoFuego2.setPosition(lugarEmisor.x,lugarEmisor.y,0.0f);

            if(sonidoFuego2.getStatus() == sf::Sound::Status::Stopped)
                sonidoFuego2.play();
            break;

        case 3:
            sonidoFuego3.setPosition(lugarEmisor.x,lugarEmisor.y,0.0f);
            if(sonidoFuego3.getStatus() == sf::Sound::Status::Stopped)
                sonidoFuego3.play();
            break;
    }

    siguienteSonido++;
    if(siguienteSonido > 3)
        siguienteSonido = 1;
}

//los siguientes sonidos se realizan en el mismo lugar donde esta
//el personaje (el listener), esto hace que la distancia a reproducir
//y la atenuacion sean atributos realtivos.
void AdministradorDeSonido::reproducirCaerenFuego()
{
    sonidoCaerEnFuego.setRelativeToListener(true);
    sonidoCaerEnFuego.play();
}

void AdministradorDeSonido::reproducirCaerEnAgua()
{
    sonidoCaerEnAgua.setRelativeToListener(true);
    sonidoCaerEnAgua.play();
}

void AdministradorDeSonido::reproducirBrinco()
{
    sonidoBrinco.setRelativeToListener(true);
    sonidoBrinco.play();
}

void AdministradorDeSonido::reproducirAlcanzarMeta()
{
    sonidoAlcanzarMeta.setRelativeToListener(true);
    sonidoAlcanzarMeta.play();
}


