//
// Created by senpai on 7/19/19.
//
#include "Motor.hpp"

Motor::Motor()
{
    //obtener la resolucion y crear la ventana
    sf::Vector2f resolucion;
    resolucion.x = sf::VideoMode::getDesktopMode().width;
    resolucion.y = sf::VideoMode::getDesktopMode().height;

    ventana.create(sf::VideoMode(resolucion.x,resolucion.y),"Tomas va tarde",sf::Style::Resize);
    //inicializamos las vistas principales
    vistaPrincipal.setSize(resolucion);

    vistaHud.reset(sf::FloatRect(0,0,resolucion.x,resolucion.y));
    //inicializamos las vistas divididas ( posInicial ,  posFinal) coordenadas OpenGL
    vistaIzquierda.setViewport(sf::FloatRect(0.001f,0.001f,0.498f,0.998f));
    vistaIzquierdaFondo.setViewport(sf::FloatRect(0.001f,0.001f,0.498f,0.998f));

                                        //(en medio      , final )
    vistaDerecha.setViewport(sf::FloatRect(0.5f,0.001f,0.499f,0.998f));
    vistaDerechaFondo.setViewport((sf::FloatRect(0.5f,0.001f,0.499f,0.998f)));

    if(!sf::Shader::isAvailable())
        ventana.close();
    else
    {
        shaderOnda.loadFromFile("../shaders/vertShader.vert",
                "../shaders/rippleShader.frag");
    }

    fondoTexture = SoporteTextura::getTextura("../graficos/background.png");
    fondoSprite.setTexture(fondoTexture);

    texAzulejos = SoporteTextura::getTextura("../graficos/barraDeAzulejos.png");

    //inicializamos el sistema de particulas
    sistemaDeParticulas.inicializar(1000);


}


void Motor::correr()
{
    sf::Clock reloj;

    while(ventana.isOpen())
    {
        sf::Time tiempo = reloj.restart();
        //actualizamos el tiempo total del juego
        tiempoTotal += tiempo;
        float segundos = tiempo.asSeconds();

        procesar_entradas();
        actualizar(segundos);
        dibujar();
    }
}
