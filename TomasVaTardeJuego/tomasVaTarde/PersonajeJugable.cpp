//
// Created by senpai on 7/21/19.
//

#include "PersonajeJugable.hpp"

void PersonajeJugable::crear(sf::Vector2f posicionInicial, float gravedad)
{
    this->posicion.x = posicionInicial.x;
    this->posicion.y = posicionInicial.y;

    this->gravedad = gravedad;

    this->sprite.setPosition(this->posicion);
}

void PersonajeJugable::actualizar(float tiempoTranscurrido)
{
    if(sePresionoDer)
        posicion.x += velocidad * tiempoTranscurrido;
    if(sePresionoIzq)
        posicion.x -= velocidad * tiempoTranscurrido;


    if(estaBrincando)
    {
        tiempoDeEsteBrinco += tiempoTranscurrido;

        if(tiempoDeEsteBrinco < duracionBrinco)
            posicion.y -= gravedad * 2 *tiempoTranscurrido; // 2 es la fuerza del brinco
        else
        {
            estaBrincando = false;
            estaCallendo = true;

        }
    }

    if(estaCallendo)
        posicion.y += gravedad * tiempoTranscurrido;

    //actualizamos los rectangulos de todas las partes del cuerpo
    //se sacaron las cantidades de cada rectangulo apoyandose
    //de manera visual de un dibujo de la division del personaje
    sf::FloatRect rectanguloTotal = this->getPosicion();

    this->piernas.left = rectanguloTotal.left + 3;
    this->piernas.top = rectanguloTotal.top + rectanguloTotal.height - 1;
    this->piernas.width = rectanguloTotal.width - 6;
    this->piernas.height = 1;

    this->lado_derecho.left = rectanguloTotal.left + rectanguloTotal.width -2;
    // el brazo esta al 35% del cuerpo completo
    this->lado_derecho.top = static_cast<float>(rectanguloTotal.top + rectanguloTotal.height * .35);
    this->lado_derecho.width = 1;
    //los brazos son el 30% en altura del cuerpo
    this->lado_derecho.height = static_cast<float>(rectanguloTotal.height * .3);

    this->lado_izquierdo.left = rectanguloTotal.left;
    this->lado_izquierdo.top = rectanguloTotal.top + rectanguloTotal.height * 35;
    this->lado_izquierdo.width = 1;
    this->lado_izquierdo.height = static_cast<float>(rectanguloTotal.height * .3);

    this->cabeza.top = static_cast<float>(rectanguloTotal.top + (rectanguloTotal.height * .3));
    this->cabeza.left = rectanguloTotal.left;
    this->cabeza.width = rectanguloTotal.width;
    this->cabeza.height = 1;

    sprite.setPosition(this->posicion);
}

sf::FloatRect PersonajeJugable::getPosicion()
{
    return this->sprite.getGlobalBounds();
}

sf::Vector2f PersonajeJugable::getCentro()
{
    return sf::Vector2f(
            posicion.x + sprite.getGlobalBounds().width/2,
            posicion.y + sprite.getGlobalBounds().height/2
            );
}

sf::Sprite PersonajeJugable::getSprite()
{
    return sprite;
}

void PersonajeJugable::pararDerecha(float posicion)
{
    this->posicion.x = posicion - sprite.getGlobalBounds().width;
    sprite.setPosition(this->posicion);
}

void PersonajeJugable::pararCaida(float posicion)
{
    this->posicion.y = posicion - getPosicion().height;
    sprite.setPosition(this->posicion);
    estaCallendo = false;
}

void PersonajeJugable::pararIzquierda(float posicion)
{
    this->posicion.x = posicion + sprite.getGlobalBounds().height;
    sprite.setPosition(this->posicion);
}

void PersonajeJugable::pararBrinco()
{
    estaBrincando = false;
    estaCallendo = true;
}

sf::FloatRect PersonajeJugable::getLadoIzquierdo()
{
    return this->lado_izquierdo;
}

sf::FloatRect PersonajeJugable::getLadoDerecho()
{
    return this->lado_derecho;
}

sf::FloatRect PersonajeJugable::getCabeza()
{
    return this->cabeza;
}

sf::FloatRect PersonajeJugable::getPiernas()
{
    return this->piernas;
}

