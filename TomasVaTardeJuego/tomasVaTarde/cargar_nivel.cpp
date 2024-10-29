//
// Created by senpai on 7/22/19.
//
#include "Motor.hpp"

void Motor::cargar_nivel()
{
    corriendo = false;
    reiniciar = false;
    //vaciamos la memoria del mapa anterior
    for(int i = 0; i < adminNiveles.getTamNivel().y; i++)
        delete[] matrizNivel[i];

    delete[] matrizNivel;

    //cargamos los datos crudos del archivo y generamos el mapa del
    //siguiente nivel
    matrizNivel = adminNiveles.siguienteNivel(nivelVA);
    //preparamos a los emisores de sonido
    poblar_emisores(emisoresDeFuego,matrizNivel);
    //reasignamos el tiempo que le corresponde al nivel
    tiempoRestante = adminNiveles.getLimiteDeTiempo();

    //creamos a los personajes en la posición inical que le corresponde
    //segun el nivel a realizar
    tomas.crear(adminNiveles.getPosicionInicial(),GRAVEDAD);
    bob.crear(adminNiveles.getPosicionInicial(),GRAVEDAD);

    seRequiereNuevoNivel = false;
}
