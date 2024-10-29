//
// Created by senpai on 7/25/19.
//

#include "Hud.hpp"

Hud::Hud()
{
    sf::Vector2u resolucion;
    resolucion.x = sf::VideoMode::getDesktopMode().width;
    resolucion.y = sf::VideoMode::getDesktopMode().height;

    fuente.loadFromFile("../fuentes/TT.ttf");

    //Mensaje que se muestra al inicio
    texInicio.setFont(fuente);
    texInicio.setCharacterSize(100);
    texInicio.setFillColor(sf::Color::White);
    texInicio.setString("presiona Enter para inciar");

    sf::FloatRect rectanguloTexto = texInicio.getGlobalBounds();

    texInicio.setOrigin(
            rectanguloTexto.left + rectanguloTexto.width/ 2.0f,
            rectanguloTexto.top + rectanguloTexto.height/2.0f
            );

    //ponemos el texto en el centro de la pantalla
    texInicio.setPosition(resolucion.x / 2.0f, resolucion.y / 2.0f);

    //tiempo
    texTiempo.setFont(fuente);
    texTiempo.setCharacterSize(75);
    texTiempo.setFillColor(sf::Color::White);
    texTiempo.setPosition(resolucion.x - 150,0);
    texTiempo.setString("------");

    //nivel
    texNivel.setFont(fuente);
    texNivel.setCharacterSize(75);
    texNivel.setFillColor(sf::Color::White);
    texNivel.setPosition(25 , 0);
    texNivel.setString("1");

    //reiniciar
    texReiniciar.setFont(fuente);
    texReiniciar.setCharacterSize(50);
    texReiniciar.setFillColor(sf::Color::White);
    texReiniciar.setPosition(resolucion.x/3,0);
    texReiniciar.setString("Presione espacio para reiniciar");


}

sf::Text Hud::getMensaje()
{
    return texInicio;
}

sf::Text Hud::getNivel()
{
    return texNivel;
}

sf::Text Hud::getTiempo()
{
    return texTiempo;
}

void Hud::setNivel(sf::String texto)
{
    this->texNivel.setString(texto);
}

void Hud::setTiempo(sf::String texto)
{
    texTiempo.setString(texto);
}

sf::Text Hud::getReiniciar()
{
    return texReiniciar;
}
