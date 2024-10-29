//
// Created by senpai on 7/19/19.
//
#include "Motor.hpp"
#include <sstream>

void Motor::actualizar(float segundos)
{
    if(seRequiereNuevoNivel)
    {
        //creamos y ajustamos lo necesario
        //para empezar el nivel
       cargar_nivel();
    }

    if(corriendo)
    {
        tomas.actualizar(segundos);
        bob.actualizar(segundos);
        //verificamos si ya se a terminado el nivel
        //el proceso es rapido y no llega a detectar las colisiones
        //de la segunda funcion al principio, por lo que
        //el personaje seguira callendo a menos que
        //se vuelva a llamar a la fución de detectar colisiones
        if(detectar_colisiones(tomas) && detectar_colisiones(bob))
        {
            //pasamos de nivel
            seRequiereNuevoNivel = true;
            //reproducimos sonido
            adminSonidos.reproducirAlcanzarMeta();

        }
        else
            detectar_colisiones(bob);

        if(tomas.getCabeza().intersects(bob.getPiernas()))
            bob.pararCaida(tomas.getCabeza().top);
        if(tomas.getPiernas().intersects(bob.getCabeza()))
            tomas.pararCaida(bob.getCabeza().top);


        //empezamos a contar el tiempo
        tiempoRestante -= segundos;
        if(tiempoRestante <= 0 || reiniciar)
            reiniciarNivel();

    }//final de if corriendo

    std::vector<sf::Vector2f>::iterator it;

    for(it = emisoresDeFuego.begin(); it != emisoresDeFuego.end(); it++)
    {
        //guardamos la posición del emisor
        float posX = (*it).x;
        float posY = (*it).y;

        //esta el emisor cerca del receptor(el Jugador)
        //creamos un rectangulo de 500 pixeles alrededor del emisor
        sf::FloatRect rectanguloLocal(posX - 250, posY - 250 , 500,500);

        if(tomas.getPosicion().intersects(rectanguloLocal))
            adminSonidos.reproducirFuego(sf::Vector2f(posX,posY),tomas.getCentro());


    }

    //ajustamos los escenarios para cada personaje
    if(pantallaDividida)
    {
        vistaDerecha.setCenter(bob.getCentro());
        vistaIzquierda.setCenter(tomas.getCentro());
    }
    else
    {
        if(jugador1)
            vistaPrincipal.setCenter(tomas.getCentro());
        else
            vistaPrincipal.setCenter(bob.getCentro());
    }

    framesDesdeUltimaActualizacionHud++;
    //checamos si es tiempo de actualizar el Hud
    if(framesDesdeUltimaActualizacionHud >= framesporActualizacionHud)
    {
       std::stringstream ssTiempo;
       std::stringstream ssNivel;

       //actualizamos el siguiente Tiempo
       ssTiempo << (int)tiempoRestante;
       hud.setTiempo(ssTiempo.str());

       //actualizamos el nivel
       ssNivel << "Nivel " << adminNiveles.getNivelActual();
       hud.setNivel(ssNivel.str());

       framesDesdeUltimaActualizacionHud = 0;
    }

    if(sistemaDeParticulas.getCorriendo())
    {
        sistemaDeParticulas.actualizar(segundos);
    }
}
