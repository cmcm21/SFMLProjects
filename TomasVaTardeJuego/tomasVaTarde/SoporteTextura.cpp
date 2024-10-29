//
// Created by senpai on 7/19/19.
//

#include "SoporteTextura.hpp"
#include <assert.h>

SoporteTextura *SoporteTextura::instancia = nullptr;

SoporteTextura::SoporteTextura()
{
    assert(this->instancia == nullptr);
    instancia = this;
}

sf::Texture& SoporteTextura::getTextura(std::string const &archivo)
{
    auto& textura = instancia->texturas;
    auto valorLlave = textura.find(archivo);
    if(valorLlave != textura.end())
        return valorLlave->second;
    else
    {
        auto &nueva = textura[archivo];
        nueva.loadFromFile(archivo);
        return nueva;
    }

}
