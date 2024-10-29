//
// Created by senpai on 7/21/19.
//

#ifndef TOMASVATARDE_PERSONAJEJUGABLE_HPP
#define TOMASVATARDE_PERSONAJEJUGABLE_HPP

#include <SFML/Graphics.hpp>

class PersonajeJugable {

protected:
    sf::Sprite sprite;
    float duracionBrinco;
    bool estaBrincando;
    bool estaCallendo;

    //dirección de movimiento
    bool sePresionoIzq;
    bool sePresionoDer;
    //que tanto ha durado el salto hasta ahora
    float tiempoDeEsteBrinco;
    bool empezoBrinco = false;  // muy util para saber cuando tocar el efecto de sonido

private:

   float gravedad;
   float velocidad = 400;
   //posición en el mundo virtual no en la pantalla(viewport)
   sf::Vector2f posicion;
   //partes del personaje

   sf::FloatRect piernas;
   sf::FloatRect cabeza;
   sf::FloatRect lado_derecho;
   sf::FloatRect lado_izquierdo;

   sf::Texture textura;

public:
    void crear(sf::Vector2f posicionInicial, float gravedad);
    bool virtual procesar_entradas() = 0;

    sf::FloatRect getPosicion();
    //partes del cuerpo
    sf::FloatRect getPiernas();
    sf::FloatRect getCabeza();
    sf::FloatRect getLadoDerecho();
    sf::FloatRect getLadoIzquierdo();

    sf::Sprite getSprite();
    void pararCaida(float posicion);
    void pararDerecha(float posicion);
    void pararIzquierda(float posicion);
    void pararBrinco();

    sf::Vector2f getCentro();

    void actualizar(float tiempoTranscurrido);
};



#endif //TOMASVATARDE_PERSONAJEJUGABLE_HPP
