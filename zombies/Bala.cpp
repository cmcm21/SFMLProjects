#include "Bala.hpp"

Bala::Bala()
{
    formaBala.setSize(sf::Vector2f(2,2));
}

void Bala::disparar(float xInical, float yInical, float xObjetivo, float yObjetivo)
{
    enVuelo = true;
    posicion.x = xInical;
    posicion.y = yInical;

    //calculamos la inclinacion de la bala, nos basamos en la ecucación de una recta
    float gradiente = (xInical - xObjetivo) / (yInical - yObjetivo);

    //la pendienete debe de ser positiva
    if(gradiente < 0)
        gradiente *= -1;

    //calculamos el radio entre x y
    float radioXY = velocidadBala / (1 + gradiente);

    //establecemos los valores de la velocidad horizontal
    balaDistanciaY = radioXY;
    balaDistanciaX = radioXY * gradiente;

    if(xObjetivo < xInical)
        balaDistanciaX *= -1;
    
    if(yObjetivo < yInical)
        balaDistanciaY *= -1;

    float rango = 1000;
    xMin = xInical - rango;
    xMax = xInical + rango;
    yMin = yInical - rango;
    yMax = yInical + rango;

    formaBala.setPosition(posicion);
}


void Bala::parar()
{
    enVuelo = false;
}


bool Bala::estaVolando()
{
    return enVuelo;
}

FloatRect Bala::getPosicion()
{
    return formaBala.getGlobalBounds();
}

RectangleShape Bala::getForma()
{
    return formaBala;
}

void Bala::actualizar(float tiempoTranscurrido)
{
    posicion.x += balaDistanciaX * tiempoTranscurrido;
    posicion.y += balaDistanciaY * tiempoTranscurrido;

    //movemos la bala
    formaBala.setPosition(posicion);
    //si la bala sale del limite
    if(posicion.x < xMin || posicion.x > xMax 
    || posicion.y < yMin || posicion.y > yMax)
        enVuelo = false;
}