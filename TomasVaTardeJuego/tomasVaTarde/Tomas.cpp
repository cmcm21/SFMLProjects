//
// Created by senpai on 7/21/19.
//

#include "Tomas.hpp"
#include "SoporteTextura.hpp"

Tomas::Tomas()
{
    sprite = sf::Sprite(SoporteTextura::getTextura("../graficos/tomas.png"));

    duracionBrinco = .45;
}

bool Tomas::procesar_entradas()
{
   empezoBrinco = false;

   if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
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

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        sePresionoIzq = true;
     else
         sePresionoIzq = false;

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        sePresionoDer = true;
     else
         sePresionoDer = false;


    return empezoBrinco;
}

