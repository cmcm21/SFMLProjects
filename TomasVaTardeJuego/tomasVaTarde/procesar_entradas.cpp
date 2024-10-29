//
// Created by senpai on 7/19/19.
//
#include "Motor.hpp"

void Motor::procesar_entradas()
{
    sf::Event evento;
    while(ventana.pollEvent(evento))
    {
        if(evento.type == sf::Event::KeyPressed)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                ventana.close();
            //empezar el juego
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                corriendo = true;
            //cambiar de juagador
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                jugador1 = !jugador1;
            //intercambiar entre pantalla completa y pantalla dividida
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
               pantallaDividida = !pantallaDividida;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                reiniciar = true;
        }
    }
 // el método procesar entradas retorna true si el salto se empezo con exito
    if(tomas.procesar_entradas())
    {
        adminSonidos.reproducirBrinco();
    }

    if(bob.procesar_entradas())
    {
        adminSonidos.reproducirBrinco();
    }
}

