#include <SFML/Graphics.hpp>

using namespace sf;

class Bala
{
private:
    Vector2f posicion;
    RectangleShape formaBala; // como es que luce la bala
    bool enVuelo; //la bala se encuentra en el aire
    float velocidadBala = 1000;
    //cuantos pixeles por segundo recorre la bala
    float balaDistanciaX;
    float balaDistanciaY;
    //variables para establecer los limites de la bala
    float xMax;
    float xMin;
    float yMax;
    float yMin;

public:
    Bala();
    void parar();
    bool estaVolando();
    void disparar(float xInicial, float yInicial,float xObjetivo,float yObjetivo);
    FloatRect getPosicion();
    RectangleShape getForma();
    void actualizar(float tiempoTranscurrido);

};