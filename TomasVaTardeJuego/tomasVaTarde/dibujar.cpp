//
// Created by senpai on 7/19/19.
//
#include "Motor.hpp"

void Motor::dibujar()
{
    ventana.clear(sf::Color::White);

    //actualizamos los parametros de los shaders
    shaderOnda.setUniform("uTime",float(tiempoTotal.asSeconds()));



    //si es pantalla completa
    if(!pantallaDividida)
    {
        ventana.setView(vistaPrincipalFondo);
        //dibujamos el fondo con shaders
        ventana.draw(fondoSprite,&shaderOnda);
        ventana.setView(vistaPrincipal);
        //dibujamos los vertices y texturas del nivel correspondiente
        ventana.draw(nivelVA,&texAzulejos);

        ventana.draw(tomas.getSprite());
        ventana.draw(bob.getSprite());
        //sistema de particulas
        if(sistemaDeParticulas.getCorriendo())
            ventana.draw(sistemaDeParticulas);

    }
    //si es pantalla dividida
    else
    {
        //izquierda (cuando dibujamos el lado izq se invierte el orden al dibujar a los personajes)
        ventana.setView(vistaIzquierdaFondo);
        //dibujamos el fondo con shaders
        ventana.draw(fondoSprite,&shaderOnda);
        ventana.setView(vistaIzquierda);

        //dibujamos el nivel
        ventana.draw(nivelVA,&texAzulejos);

        //bob se dibuja primero
        ventana.draw(bob.getSprite());
        //cuando se dibuje a tomas este hara que bob se recorra
        //por lo tanto tomas estara del lado izq y bob del lado derecho
        //como estaba establecido
        ventana.draw(tomas.getSprite());
        //dibujamos el sistema de particulas
        if(sistemaDeParticulas.getCorriendo())
            ventana.draw(sistemaDeParticulas);


        //===========================================LA OTRA MITAD DE PANTALLA======================================


        //derecha del lado derecho de dibuja de forma normal(como estaba establcido)
        ventana.setView(vistaDerechaFondo);
        //dibujamos el fondo con shaders
        ventana.draw(fondoSprite,&shaderOnda);
        ventana.setView(vistaDerecha);
        //dibujamos el nivel
        ventana.draw(nivelVA,&texAzulejos);

        ventana.draw(tomas.getSprite());
        ventana.draw(bob.getSprite());
        if(sistemaDeParticulas.getCorriendo())
            ventana.draw(sistemaDeParticulas);
    }
    ventana.setView(vistaHud);
    ventana.draw(hud.getNivel());
    ventana.draw(hud.getTiempo());
    ventana.draw(hud.getReiniciar());
    if(!corriendo)
       ventana.draw(hud.getMensaje());

    ventana.display();
}
