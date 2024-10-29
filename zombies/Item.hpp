#include <SFML/Graphics.hpp>

using namespace sf;

class Item 
{
private:
    const int VALOR_VIDA_INICIAL = 50;
    const int VALOR_MUNICION_INICIAL = 12;
    const int INICIA_TIEMPO_ESPERA = 10;//cuanto tiempo se encuentra el objeto antes de desaparecer
    const int INICIA_SEGUNDOS_DE_VIDA = 5;

    Sprite sprite;
    IntRect area;
    int valor;
    int tipo; //tipo de item 1 = vida, 2 = municion

    //variables para manejar la creación y desaparición de items
    bool creado;
    float segundosDesdeCracion;
    float segundosDesdeDesaparicion;
    float segundosDeVida;
    float segundosDeEspera;
public:
    Item(int tipo);

    void setArea(IntRect area);
    void crear();
    FloatRect getPosicion();
    Sprite getSprite();
    void actualizar(float tiempoTranscurrido);
    bool estaCreado();
    int cachar();
    void mejorar(); // mejoramos el valor de cada item


};