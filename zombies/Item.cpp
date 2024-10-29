#include "Item.hpp"
#include "SoporteTextura.hpp"

Item::Item(int tipo)
{
    this->tipo = tipo;
    if(tipo == 1)
    {
        sprite = Sprite(SoporteTextura::getTextura("gráficos/botiquin.png"));
        valor = VALOR_VIDA_INICIAL;
    }
    else
    {
        sprite = Sprite(SoporteTextura::getTextura("gráficos/municion_recoger.png"));
        valor = VALOR_MUNICION_INICIAL;
    }

    sprite.setOrigin(25,25);
    segundosDeEspera = INICIA_TIEMPO_ESPERA;
    segundosDeVida = INICIA_SEGUNDOS_DE_VIDA;
}

void Item::setArea(IntRect area)
{
    this->area.left = area.left + 100;
    this->area.width = area.width - 100;
    this->area.top = area.top + 100;
    this->area.height = area.height - 100;   

    crear();
}

void Item::crear()
{
    //crear en una posición aleatoria
    srand((int)time(0) / tipo);
    int x = (rand() % area.width);
    srand((int)time(0) / tipo);
    int y = (rand() % area.height);
    
    segundosDesdeCracion = 0;
    creado = true;
    sprite.setPosition(x,y);
}

FloatRect Item::getPosicion()
{
    return sprite.getGlobalBounds();
}

Sprite Item::getSprite()
{
    return sprite;
}

bool Item::estaCreado()
{
    return creado;
}

int Item::cachar()
{
    creado = false;
    segundosDesdeDesaparicion = 0;
    return valor;
}

void Item::actualizar(float tiempoTranscurrido)
{
    if(creado)
        segundosDesdeCracion += tiempoTranscurrido;
    else
        segundosDesdeDesaparicion += tiempoTranscurrido;

    //esconder el item
    if(segundosDesdeCracion > segundosDeVida && creado)
    {
        creado = false;
        segundosDesdeCracion = 0;
    }

    if(segundosDesdeDesaparicion > segundosDeEspera && !creado)
        crear();
}

void Item::mejorar()
{
    if(tipo == 1)
        valor += (VALOR_MUNICION_INICIAL * .5);
    else
        valor += (VALOR_VIDA_INICIAL * .5);
    
    //hacerlos más frecuentes y con más vida
    segundosDeVida += (INICIA_SEGUNDOS_DE_VIDA / 10);
    segundosDeEspera -= (INICIA_TIEMPO_ESPERA / 10);
    
}
















