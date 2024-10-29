// // Created by senpai on 7/25/19. //
#ifndef TOMASVATARDE_HUD_HPP
#define TOMASVATARDE_HUD_HPP
#include <SFML/Graphics.hpp>

class Hud {

private:
    sf::Font fuente;
    sf::Text texInicio;
    sf::Text texTiempo;
    sf::Text texNivel;
    sf::Text texReiniciar;

public:
    Hud();
    sf::Text getMensaje();
    sf::Text getNivel();
    sf::Text getTiempo();
    sf::Text getReiniciar();

    void setNivel(sf::String texto);
    void setTiempo(sf::String texto);


};


#endif //TOMASVATARDE_HUD_HPP
