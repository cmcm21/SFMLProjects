//
// Created by senpai on 7/25/19.
//

#ifndef TOMASVATARDE_SISTEMADEPARTICULAS_HPP
#define TOMASVATARDE_SISTEMADEPARTICULAS_HPP

#include <SFML/Graphics.hpp>
#include "Particula.hpp"

class SistemaDeParticulas : public sf::Drawable{

private:
    std::vector<Particula> particulas;
    sf::VertexArray vertices;
    float duracion;
    bool estaCorriendo = false;

public:
    void virtual draw(sf::RenderTarget &objetivo,sf::RenderStates estados) const;
    void inicializar(int numParticulas);
    void emitirParticulas(sf::Vector2f posicion);
    void actualizar(float tiempoTranscurrido);
    bool getCorriendo();
};


#endif //TOMASVATARDE_SISTEMADEPARTICULAS_HPP
