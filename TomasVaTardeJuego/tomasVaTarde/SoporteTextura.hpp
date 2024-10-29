//
// Created by senpai on 7/19/19.
//

#ifndef TOMASVATARDE_SOPORTETEXTURA_HPP
#define TOMASVATARDE_SOPORTETEXTURA_HPP

#include <SFML/Graphics.hpp>
#include <map>

class SoporteTextura {
private:
    std::map<std::string,sf::Texture> texturas;
    static SoporteTextura* instancia;

public:
    SoporteTextura();
    static sf::Texture& getTextura(std::string const &archivo);

};


#endif //TOMASVATARDE_SOPORTETEXTURA_HPP
