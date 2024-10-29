//
// Created by senpai on 7/22/19.
//

#ifndef TOMASVATARDE_ADMINISTRADORDENIVELES_HPP
#define TOMASVATARDE_ADMINISTRADORDENIVELES_HPP
#include <SFML/Graphics.hpp>

const int BLOQUE_NORMAL = 1;
const int BLOQUE_FUEGO = 2;
const int BLOQUE_AGUA = 3;
const int BLOQUE_FIN = 4;

class AdministradorDeNiveles {

private:
    sf::Vector2i tamNivel;
    sf::Vector2f posicionInicial;
    float modificadorDeTiempo = 1; // lo utilizamos para hacer cada nuevo juego más dificil
    float limiteDeTiempoBase = 0;
    int nivelActual = 0;
    const int numNiveles = 4;

public:
    const int TAM_AZULEJO = 50;
    const int VERTICES = 4;

    float getLimiteDeTiempo();
    sf::Vector2f getPosicionInicial();

    int **siguienteNivel(sf::VertexArray &nivel);
    sf::Vector2i getTamNivel();
    int getNivelActual();
    void setNivelActual(int nivel);
};


#endif //TOMASVATARDE_ADMINISTRADORDENIVELES_HPP
