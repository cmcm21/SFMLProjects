#include "Arena.hpp"

Zombie *crearHorda(int numZombies, IntRect arena)
{
    Zombie *zombies = new Zombie[numZombies];

    //agregamos y desminuimos 20 pixeles para que los zombies se detengan
    //en el muro de piedra.
    int maxY = arena.height - 100;
    int minY = arena.top + 100;
    int maxX = arena.width - 100;
    int minX = arena.left + 100;

    for(int i = 0; i < numZombies; i++)
    {
        //para que los zombies aparezcan en una posción aleatoria
        srand((int)time(0) * i);
        int lado = (rand() % 4);
        float x,y;

        switch (lado)
        {
        case 0:
            //aparece a la izquierda
            x = minX;
            y = (rand() % maxY) + minY;
            break;
        
        case 1:
            //aparece a la derecha
            x = maxX;
            y = (rand() % maxY) + minY;
            break;

        case 2:
            //aparece arriba
            y = minY;
            x = (rand() % maxX) + minX;
            break;

        case 3:
            //aparece abajo
            y = maxY;
            x = (rand() % maxX) + minX;
            break;
        }//fin de switch
        //decidimos aleatoriamente el tipo de zombie que sale
        srand((int)time(0) * i * 2);
        int tipo = (rand() % 3);
        //creamo al zombie
        zombies[i].crear(x,y,tipo,i);
    }//fin de for
    return zombies;
}