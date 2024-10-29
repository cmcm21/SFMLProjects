//
// Created by senpai on 7/24/19.
//

#ifndef TOMASVATARDE_ADMINISTRADORDESONIDO_HPP
#define TOMASVATARDE_ADMINISTRADORDESONIDO_HPP

#include <SFML/Audio.hpp>

class AdministradorDeSonido {
private:

    //buffer
    sf::SoundBuffer bufferFuego;
    sf::SoundBuffer bufferCaerEnFuego;
    sf::SoundBuffer bufferCaerEnAgua;
    sf::SoundBuffer bufferBrinco;
    sf::SoundBuffer bufferAlcanzarMeta;

    //sonidos
    sf::Sound sonidoFuego1;
    sf::Sound sonidoFuego2;
    sf::Sound sonidoFuego3;
    sf::Sound sonidoCaerEnFuego;
    sf::Sound sonidoCaerEnAgua;
    sf::Sound sonidoBrinco;
    sf::Sound sonidoAlcanzarMeta;

    //contador para los 3 sonidos de fuego
    int siguienteSonido = 1;

public:
    AdministradorDeSonido();

    void reproducirFuego(sf::Vector2f lugarEmisor, sf::Vector2f lugarReceptor);
    void reproducirCaerenFuego();
    void reproducirCaerEnAgua();
    void reproducirBrinco();
    void reproducirAlcanzarMeta();

};


#endif //TOMASVATARDE_ADMINISTRADORDESONIDO_HPP
