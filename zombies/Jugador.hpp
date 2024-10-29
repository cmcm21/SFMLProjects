#include <SFML/Graphics.hpp>

using namespace sf;

class Jugador
{
private:
    const float VELOCIDAD_INICIAL = 200;
    const float VIDA_INCIAL = 100;
    
    Vector2f posicion; // donde se encuentra el jugador
    Sprite sprite;
    Texture textura;
    Vector2f resolucion;
    IntRect arena; //tanaño del arena actual
    int tamAzulejo;

    //hacia cual dirección esta el jugador moviendose
    bool arribaPresionado;
    bool abajoPresionado;
    bool izquierdaPresionado;
    bool derechaPresionado;

    //que tanta vida tiene el jugador
    int vida;

    //cual es el limite de vida del jugador
    int maxVida;
    //cuando fue el ultimo golpe del jugador
    Time ultimoGolpe;
    //velocidad de pixeles por segundo
    float velocidad;
public:
    Jugador();

    void engendrar(IntRect area, Vector2f resolucion, int tamAzulejo);

    void recetearJugador(); // se llama este método al final de cada juego

    bool golpear(Time tiempoGolpe); // se trata con el proceso de golpear un zombie

    Time getUltimoGolpe();
    FloatRect getPosicion();
    Vector2f getCentro();
    float getRotacion();
    Sprite getSprite();
    int getVida();

    //métodos para mover al jugador
    void moverDerecha();
    void moverIzquierda();
    void moverArriba();
    void moverAbajo();

    //detener al jugador en una dirección
    void pararDerecha();
    void pararIzquierda();
    void pararArriba();
    void pararAbajo();

    void actualizar(float tiempoTranscurrido, Vector2i posicionMouse);

    void aumentarVelocidad();
    void aumentarVida();

    void incrementarNivelDeVida(int cantidad);


};