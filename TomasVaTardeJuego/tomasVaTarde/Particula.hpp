//
// Created by senpai on 7/25/19.
//

#ifndef TOMASVATARDE_PARTICULA_HPP
#define TOMASVATARDE_PARTICULA_HPP

#include <SFML/Graphics.hpp>

class Particula {

private:
    sf::Vector2f posicion;
    sf::Vector2f velocidad;

public:
    Particula(sf::Vector2f direccion);

    void actualizar(float segundos);
    void setPosicion(sf::Vector2f posicion);
    sf::Vector2f getPosicion();

};


#endif //TOMASVATARDE_PARTICULA_HPP
