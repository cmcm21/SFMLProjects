#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
    //Velocidades de los zombies
    const float velocidad_gloton = 40;
    const float velocidad_cazador = 80;
    const float velocidad_salvaje = 20;
    //dificultad de cada zomibe
    const float vida_gloton = 5;
    const float vida_cazador = 1;
    const float vida_salvaje = 3;
    //variacion de velocidad de cada zombie
    const int VAR_MAXIMA = 30;
    const int OFFSET = 101 - VAR_MAXIMA;

    Vector2f posicion;
    Sprite sprite;
    float velocidad;
    float vida;
    bool conVida;
public:
    bool impacto(); //maneja cuando una bala inpacta al zombie
    bool estaVivo();
    void crear(float xInicial, float yInicial, int tipo, int semilla);
    FloatRect getPosicion(); //saber en que rectangulo se encuentra el zombie
    Sprite getSprite();
    void actualizar(float tiempoTranscurrido,Vector2f posicionJugador);
};