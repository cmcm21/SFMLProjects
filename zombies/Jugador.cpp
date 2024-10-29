#include "Jugador.hpp"
#include <math.h>
#include "SoporteTextura.hpp"


Jugador::Jugador()
{
    velocidad = VELOCIDAD_INICIAL;
    vida = VIDA_INCIAL;
    maxVida = VIDA_INCIAL;

    textura = SoporteTextura::getTextura("gráficos/jugador.png");
    sprite.setTexture(textura);

    sprite.setOrigin(25,25);
}

void Jugador::engendrar(IntRect arena,Vector2f resolucion, int tamAzulejo)
{
    //Colocamos al jugador en medio del arena
    posicion.x = arena.width / 2;
    posicion.y = arena.height / 2;

    //copiamos los atributos de la arena
    this->arena.height = arena.height;
    this->arena.width = arena.width;
    this->arena.top = arena.top;
    this->arena.left = arena.left;

    //copiamos el tam del titulo
    this->tamAzulejo = tamAzulejo;

    this->resolucion.x = resolucion.x;
    this->resolucion.y = resolucion.y;
}

void Jugador::recetearJugador()
{
    velocidad = VELOCIDAD_INICIAL;
    vida = VIDA_INCIAL;
    maxVida = VIDA_INCIAL;
}

Time Jugador::getUltimoGolpe()
{
    return this->ultimoGolpe;
}

bool Jugador::golpear(Time tiempoGolpe)
{
    if(tiempoGolpe.asMilliseconds()  -  this->ultimoGolpe.asMilliseconds() > 200)
    {
        this->ultimoGolpe = tiempoGolpe;
        vida -= 10;
        return true;
    }
    else
    {
        return false;
    }
}

FloatRect Jugador::getPosicion()
{
    return this->sprite.getGlobalBounds();
}

Vector2f Jugador::getCentro()
{
    return this->posicion;
}

float Jugador::getRotacion()
{
    return this->sprite.getRotation();
}

Sprite Jugador::getSprite()
{
    return this->sprite;
}

int Jugador::getVida()
{
    return this->vida;
}

void Jugador::moverAbajo()
{
    abajoPresionado = true;
}

void Jugador::moverArriba()
{
    arribaPresionado = true;
}

void Jugador::moverDerecha()
{
    derechaPresionado = true;
}

void Jugador::moverIzquierda()
{
    izquierdaPresionado = true;
}

void Jugador::pararAbajo()
{
    abajoPresionado = false;
}

void Jugador::pararArriba()
{
    arribaPresionado = false;
}

void Jugador::pararDerecha()
{
    derechaPresionado = false;
}

void Jugador::pararIzquierda()
{
    izquierdaPresionado = false;
}

void Jugador::actualizar(float tiempoTranscurrido, Vector2i posicionMouse)
{
    if(arribaPresionado)
        posicion.y -= velocidad * tiempoTranscurrido;
    if(abajoPresionado)
        posicion.y += velocidad * tiempoTranscurrido;
    if(derechaPresionado)
        posicion.x += velocidad * tiempoTranscurrido;
    if(izquierdaPresionado)
        posicion.x -= velocidad * tiempoTranscurrido;
    
    sprite.setPosition(posicion);
    
    //mantener al jugador dentro del arena
    if(posicion.x > arena.width - tamAzulejo)
        posicion.x = arena.width - tamAzulejo;
    if(posicion.x < arena.left + tamAzulejo)
        posicion.x = arena.left + tamAzulejo;
    if(posicion.y > arena.height - tamAzulejo)
        posicion.y = arena.height - tamAzulejo;
    if(posicion.y < arena.top + tamAzulejo)
        posicion.y = arena.top + tamAzulejo;
    
    //calculo del frente del jugador
    float angulo = (atan2(posicionMouse.y - resolucion.y /2 , posicionMouse.x - resolucion.x / 2) * 180) / 3.141;
    
    this->sprite.setRotation(angulo);
}


void Jugador::aumentarVelocidad()
{
    //aumentamos un 20% la velocidad
    velocidad += (VELOCIDAD_INICIAL * .2);
}

void Jugador::aumentarVida()
{
    //aumentamos un 20% la vida
    maxVida += (VIDA_INCIAL * .2);
}

void Jugador::incrementarNivelDeVida(int cantidad)
{
    vida += cantidad;

    if(vida > maxVida)
        vida = maxVida;
}