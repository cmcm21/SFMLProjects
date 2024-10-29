#include "Zombie.hpp"
#include "SoporteTextura.hpp"
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

void Zombie::crear(float xInicial, float yInicial, int tipo, int semilla)
{
    conVida = true;
    switch (tipo)
    {
    case 0: // gloton
        sprite = Sprite(SoporteTextura::getTextura("gráficos/gloton.png"));
        velocidad = 40;
        vida = 5;
        break;
    case 1://cazador
        sprite = Sprite(SoporteTextura::getTextura("gráficos/cazador.png"));
        vida = 1;
        velocidad = 70;
        break;    
    case 2: // salvaje
        sprite = Sprite(SoporteTextura::getTextura("gráficos/salvaje.png"));
        vida = 3;
        velocidad = 20;
        break;
    }

    //modificamos la semilla para hacer a cada zombie unico
    srand((int)time(0) * semilla);
    //en algun lugar entre 80 y 100
    float modificador = (rand() % VAR_MAXIMA) + OFFSET;

    modificador /= 100; // lo ocupamos en fracción de 1
    velocidad *= modificador;
    
    posicion.x = xInicial;
    posicion.y = yInicial;
    //colocamos el origen al centro
    sprite.setOrigin(25,25);
    sprite.setPosition(posicion);
}

bool Zombie::impacto()
{
    vida--;
    if(vida < 0)
    {
        conVida = false;
        sprite.setTexture(SoporteTextura::getTextura("gráficos/sangre.png"));
        return true;
    }
    //infligue daño pero no mata
    return false;
}

bool Zombie::estaVivo()
{
    return conVida;
}

Sprite Zombie::getSprite()
{
    return sprite;
}

FloatRect Zombie::getPosicion()
{
    return sprite.getGlobalBounds();
}

void Zombie::actualizar(float tiempoTranscurrido,Vector2f posicionJugador)
{
    float x_jugador = posicionJugador.x;
    float y_jugador = posicionJugador.y;
    //logica para que el zombie persiga al jugador
    if(x_jugador > posicion.x)
        posicion.x = posicion.x + velocidad * tiempoTranscurrido;
    if(y_jugador > posicion.y)
        posicion.y = posicion.y + velocidad * tiempoTranscurrido;
    if(x_jugador < posicion.x)
        posicion.x = posicion.x - velocidad * tiempoTranscurrido;
    if(y_jugador < posicion.y)
        posicion.y = posicion.y - velocidad * tiempoTranscurrido;
    
    sprite.setPosition(posicion);

    //que el zombie volte hacia la dirección del jugador
    float angulo = (atan2(y_jugador - posicion.y, x_jugador - posicion.x)* 180)/3.141;
    sprite.setRotation(angulo);
}