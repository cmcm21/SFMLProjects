//
// Created by senpai on 7/25/19.
//

#include "SistemaDeParticulas.hpp"
#include <cmath>

void SistemaDeParticulas::draw(sf::RenderTarget &objetivo, sf::RenderStates estados) const
{
    objetivo.draw(vertices,estados);
}

void SistemaDeParticulas::inicializar(int numParticulas)
{
    vertices.setPrimitiveType(sf::Points);
    vertices.resize(numParticulas);

    //creamos las particulas
    for(int i = 0; i < numParticulas; i++)
    {
        srand(time(0) + i);
        float angulo = (rand() % 360 ) * 3.14 / 180.0f;
        float velocidad = (rand() & 600) + 600.0f;

        sf::Vector2f direccion;

        direccion = sf::Vector2f(cos(angulo) * velocidad, sin(angulo) * velocidad);

        particulas.push_back(Particula(direccion));
    }
}

void SistemaDeParticulas::emitirParticulas(sf::Vector2f posicion)
{
    estaCorriendo = true;
    duracion = 2;

    std::vector<Particula>::iterator it;
    int verticeActual = 0;
    for(it = particulas.begin(); it != particulas.end(); it++)
    {
        vertices[verticeActual].color = sf::Color::Yellow;
        (*it).setPosicion(posicion);

        verticeActual++;
    }
}

void SistemaDeParticulas::actualizar(float tiempoTranscurrido)
{
    this->duracion -= tiempoTranscurrido;
    int verticeActual = 0;

    for(std::vector<Particula>::iterator it = particulas.begin(); it != particulas.end(); it++)
    {
        (*it).actualizar(tiempoTranscurrido);
        vertices[verticeActual].position = (*it).getPosicion();
        verticeActual++;
    }

    if(duracion < 0)
        this->estaCorriendo = false;


}

bool SistemaDeParticulas::getCorriendo()
{
    return estaCorriendo;
}
