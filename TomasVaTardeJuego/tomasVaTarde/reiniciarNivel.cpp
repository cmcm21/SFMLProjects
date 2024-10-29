//
// Created by senpai on 7/25/19.
//
#include "Motor.hpp"

void Motor::reiniciarNivel()
{
    seRequiereNuevoNivel = true;
    int nivel = adminNiveles.getNivelActual();
    nivel--;
    adminNiveles.setNivelActual(nivel);
}
