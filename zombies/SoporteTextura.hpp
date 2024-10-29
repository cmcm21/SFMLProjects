#ifndef _SOPORTE_TEXTURA_HPP
#define _SOPORTE_TEXTURA_HPP
#include <SFML/Graphics.hpp>
#include<map>

using namespace std;
using namespace sf;


class SoporteTextura
{
private:
    std::map<std::string,Texture> texturas;

    //solo se va a poder crear una instancia de esta clase
    static SoporteTextura *_instancia;
public:
    SoporteTextura();
    static Texture &getTextura(std::string const &archivo);
};


#endif