//
// Created by senpai on 7/25/19.
//

#include "Motor.hpp"

void Motor::poblar_emisores(std::vector<sf::Vector2f> &emisoresDeSonido, int **matrizNivel)
{
    //el vector debe de estar vacio
    emisoresDeSonido.clear();

    //por lago de fuego
    //solo queremos que un bloque realize el sondio
    //del lago
    sf::FloatRect emisorPrevio;

    //buscamos los bloques de fuego
    for(int x = 0; x < adminNiveles.getTamNivel().x;x++)
    {
        for(int y = 0; y < adminNiveles.getTamNivel().y; y++)
        {
            if(matrizNivel[y][x] == BLOQUE_FUEGO) // fuego
            {
               //si no hay un azulejo previo entonces lo creamos
               if(!sf::FloatRect(x * TAM_AZULEJO, y*TAM_AZULEJO,
                       TAM_AZULEJO,TAM_AZULEJO).intersects(emisorPrevio))
               {

                 //añadimos las cordenadas del bloque
                 emisoresDeSonido.push_back(sf::Vector2f(x * TAM_AZULEJO,y * TAM_AZULEJO));

                 //hacemos un rectangulo de 6 x 6 para
                 //abarcar por completo al lago de fuego
                 emisorPrevio.left = x * TAM_AZULEJO;
                 emisorPrevio.top = y * TAM_AZULEJO;
                 emisorPrevio.width = TAM_AZULEJO * 6;
                 emisorPrevio.height = TAM_AZULEJO * 6;
               }

            }
        }//fin del for de y
    }//fin del for de x
}