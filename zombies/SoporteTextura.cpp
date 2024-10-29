#include "SoporteTextura.hpp"
#include <assert.h>

SoporteTextura* SoporteTextura::_instancia = nullptr;
SoporteTextura::SoporteTextura()
{
    assert(_instancia == nullptr);
    _instancia = this;
}

sf::Texture& SoporteTextura::getTextura(std::string const &archivo)
{
    //tomamos una referencia de la instancia hacia el contenedor map para utilizarlo
    auto &mapa = _instancia->texturas;

    auto parValorLlave = mapa.find(archivo);

    if(parValorLlave != mapa.end())//lo encontramos??
    {
        //regresamo como valor la textura si se llega a encontrar
        return parValorLlave->second;
    }
    else // si no se encuentra lo creamos
    {
        auto &textura = mapa[archivo];//creamos un nuevo par con una textura y el archivo

        textura.loadFromFile(archivo);
        return textura;
    }
}