//
// Created by senpai on 7/21/19.
//

#include "Bob.hpp"
#include "SoporteTextura.hpp"
#include <iostream>

Bob::Bob()
{
   sprite = sf::Sprite(SoporteTextura::getTextura("../graficos/bob.png")) ;
   duracionBrinco = .25;
}

bool Bob::procesar_entradas()
{
    empezoBrinco = false;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(!estaBrincando && !estaCallendo)
        {
            estaBrincando = true;
            tiempoDeEsteBrinco = 0;
            empezoBrinco = true;
        }
    }
    else
    {
        estaBrincando = false;
        estaCallendo = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        sePresionoDer = true;
    else
        sePresionoDer = false;
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
       sePresionoIzq = true;
   else
       sePresionoIzq = false;

    return empezoBrinco;
}
