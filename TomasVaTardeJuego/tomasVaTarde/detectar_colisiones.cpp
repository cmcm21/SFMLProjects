//
// Created by senpai on 7/24/19.
//
#include "Motor.hpp"

bool Motor::detectar_colisiones(PersonajeJugable &personaje)
{
    bool objetivoAlcanzado = false;

    sf::FloatRect zonaDeDeteccion = personaje.getPosicion();
    sf::FloatRect bloque;

    bloque.height = TAM_AZULEJO;
    bloque.width = TAM_AZULEJO;

    //construimos un area alrededor de tomas para detectar colisiones
    int xInicial = (int)(zonaDeDeteccion.left/TAM_AZULEJO) -1;
    int yInicial = (int)(zonaDeDeteccion.top / TAM_AZULEJO) -1;
    int xFinal = (int)(zonaDeDeteccion.left / TAM_AZULEJO) + 2;
    //tomas es un rectangulo por lo que tiene mayor altura
    int yFinal = (int)(zonaDeDeteccion.top / TAM_AZULEJO) + 3;

    //nos aseguramos de no detectar colisiones con objetos
    //que no exiten
    if(xInicial < 0) xInicial = 0;
    if(yInicial < 0) yInicial = 0;
    if(xFinal >= this->adminNiveles.getTamNivel().x) xFinal = adminNiveles.getTamNivel().x;
    if(yFinal >= this->adminNiveles.getTamNivel().y) yFinal = adminNiveles.getTamNivel().y;

    //Cuando el personaje se caiga
    //area rectangular que abarca todo el mapa del nivel
    sf::FloatRect nivel(0,0,
            adminNiveles.getTamNivel().x * TAM_AZULEJO,
            adminNiveles.getTamNivel().y * TAM_AZULEJO
            );

    if(!personaje.getPosicion().intersects(nivel)) // si deja de hacer intersección con el mapa
        personaje.crear(adminNiveles.getPosicionInicial(),GRAVEDAD);


    for(int x = xInicial; x < xFinal; x++)
    {
        for(int y = yInicial; y < yFinal; y++)
        {
            bloque.left = x * TAM_AZULEJO;
            bloque.top = y * TAM_AZULEJO;

            //verificamos si el jugador se quema o si se ahoga
            if(matrizNivel[y][x] == BLOQUE_FUEGO || matrizNivel[y][x] == BLOQUE_AGUA)
            {
                if(personaje.getCabeza().intersects(bloque))
                {
                    personaje.crear(adminNiveles.getPosicionInicial(),GRAVEDAD);
                    if(matrizNivel[y][x] == BLOQUE_FUEGO) //fuego
                        //reproducir sonido
                        adminSonidos.reproducirCaerenFuego();
                    else //agua
                       //reproducir sonido
                       adminSonidos.reproducirCaerEnAgua();
                }
            }

            //si el personaje hace contacto con un bloque normal
            if(matrizNivel[y][x] == BLOQUE_NORMAL)
            {
                if(personaje.getLadoDerecho().intersects(bloque))
                    personaje.pararDerecha(bloque.left);
                else if(personaje.getLadoIzquierdo().intersects(bloque))
                    personaje.pararIzquierda(bloque.left);


                if(personaje.getPiernas().intersects(bloque))
                    personaje.pararCaida(bloque.top);
                else if(personaje.getCabeza().intersects(bloque))
                   personaje.pararBrinco();
            }

            //el personaje ha hecho contacto con el fuego o el agua?
            if(!sistemaDeParticulas.getCorriendo())
            {
                if(matrizNivel[y][x] == BLOQUE_FUEGO || matrizNivel[y][x] == BLOQUE_AGUA)
                {
                    if(personaje.getPiernas().intersects(bloque))
                        sistemaDeParticulas.emitirParticulas(personaje.getCentro());
                }
            }

            if(matrizNivel[y][x] == BLOQUE_FIN)
                objetivoAlcanzado = true;

        } // fin del segundo for
    } //fin del primer for

    return objetivoAlcanzado;
}
