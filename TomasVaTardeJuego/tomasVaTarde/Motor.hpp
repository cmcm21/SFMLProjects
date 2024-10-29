//
// Created by senpai on 7/19/19.
//

#ifndef TOMASVATARDE_MOTOR_HPP
#define TOMASVATARDE_MOTOR_HPP

#include <SFML/Graphics.hpp>
#include "SoporteTextura.hpp"
#include "Tomas.hpp"
#include "Bob.hpp"
#include "AdministradorDeNiveles.hpp"
#include "AdministradorDeSonido.hpp"
#include "Hud.hpp"
#include "SistemaDeParticulas.hpp"
#include "SistemaDeParticulas.hpp"
#include <vector>


class Motor {
private:
    SoporteTextura soporte_textura;
    //personajes
    Tomas tomas;
    Bob bob;
    //creamos el sistema de particulas
    SistemaDeParticulas sistemaDeParticulas;

    //admins
    AdministradorDeNiveles adminNiveles;
    AdministradorDeSonido adminSonidos;

    //hud
    Hud hud;
    int framesDesdeUltimaActualizacionHud = 0;
    int framesporActualizacionHud = 500;


    const int TAM_AZULEJO = 50; //cada azulejo(cuadro) de pixeles en la imagen tiles_sheet.png es de 50x50 pixeles
    const int VERTICES = 4;
    const int GRAVEDAD = 300;

    sf::RenderWindow ventana;
    //vistas principales
    sf::View vistaPrincipal;
    sf::View vistaIzquierda;
    sf::View vistaDerecha;

    //vistas de fondo
    sf::View vistaPrincipalFondo;
    sf::View vistaIzquierdaFondo;
    sf::View vistaDerechaFondo;

    sf::View vistaHud;

    sf::Sprite fondoSprite;
    sf::Texture fondoTexture;

    sf::Shader shaderOnda;

    bool reiniciar = false;
    //estado del juego
    bool corriendo = false;
    //intercambiamos entre el jugador1 y el jugador2(bob y tomas)
    bool jugador1 = true;
    //iniciamos en pantalla completa
    bool pantallaDividida = false;
    //Tiempo para el nivel
    float tiempoRestante = 10;//10 solo para probar

    sf::Time tiempoTotal;
    //se inicia un nuevo nivel o el primer nivel
    bool seRequiereNuevoNivel = true;
    //vertexArray para la elaboración del entorno gráfico del nivel
    sf::VertexArray nivelVA;
    //la información de forma cruda desde el archivo
    int **matrizNivel = nullptr;

    sf::Texture texAzulejos;

    //métodos privados
    void procesar_entradas();
    void actualizar(float segundos);
    void dibujar();

    void cargar_nivel();

    bool detectar_colisiones(PersonajeJugable &personaje);

    void poblar_emisores(std::vector <sf::Vector2f> &emisoresDeSonido, int **matrizNivel);
    std::vector<sf::Vector2f> emisoresDeFuego;
    void reiniciarNivel();
public:
    Motor();
    void correr();

};


#endif //TOMASVATARDE_MOTOR_HPP
