//
// Created by senpai on 7/25/19.
//

#include "Particula.hpp"

Particula::Particula(sf::Vector2f direccion)
{
    velocidad.x = direccion.x;
    velocidad.y = direccion.y;
}

void Particula::actualizar(float segundos)
{
    //no hay necesidad de tratar al eje x y eje y por separado
    posicion += velocidad * segundos;
}

void Particula::setPosicion(sf::Vector2f posicion)
{
    this->posicion = posicion;
}

sf::Vector2f Particula::getPosicion()
{
    return posicion;
}
