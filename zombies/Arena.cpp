#include "Arena.hpp"

int crearFondo(VertexArray &va,IntRect arena)
{
    //cualquier cosa que hagamos en esta funcion se 
    //refleja en el fonde de pantalla del juego
    const int TAM_AZULEJOS = 50;
    const int TIPO_AZULEJOS = 3;
    const int VERTICES = 4;

    int mundoWidth = arena.width / TAM_AZULEJOS;
    int mundoHeight = arena.height / TAM_AZULEJOS;

    va.setPrimitiveType(Quads); // utilizaremos un tipo de figura que ocupe 4 vertices
    va.resize(mundoWidth * mundoHeight * VERTICES);

    int verticeActual = 0;
    for(int w = 0; w < mundoWidth; w++)
    {
        for(int h = 0; h < mundoHeight; h++)
        {
            //colocamos las coordenadas de cada vertice para el cuadrado
            va[verticeActual + 0].position = 
                Vector2f(w * TAM_AZULEJOS, h * TAM_AZULEJOS);
            va[verticeActual + 1].position = 
                Vector2f((w * TAM_AZULEJOS) + TAM_AZULEJOS, h * TAM_AZULEJOS);
            va[verticeActual + 2].position = 
                Vector2f((w * TAM_AZULEJOS) + TAM_AZULEJOS, (h * TAM_AZULEJOS) + TAM_AZULEJOS);
            va[verticeActual + 3].position = 
                Vector2f(w * TAM_AZULEJOS, (h * TAM_AZULEJOS) + TAM_AZULEJOS);
            

            //definimos las texturas de los limites del fondo de pantalla
            if(h == 0 || w == 0 || h == mundoHeight - 1 || w == mundoWidth - 1)
            {
                va[verticeActual + 0].texCoords = 
                    Vector2f(0,0 + TIPO_AZULEJOS * TAM_AZULEJOS);
                va[verticeActual + 1].texCoords = 
                    Vector2f(TAM_AZULEJOS, 0 + TIPO_AZULEJOS * TAM_AZULEJOS);
                va[verticeActual + 2].texCoords = 
                    Vector2f(TAM_AZULEJOS, TAM_AZULEJOS + TIPO_AZULEJOS * TAM_AZULEJOS);
                va[verticeActual + 3].texCoords = 
                    Vector2f(0,TAM_AZULEJOS + TIPO_AZULEJOS * TAM_AZULEJOS);

            }
            //si no son los limites de la pantalla utilizamos una textura random
            else
            {
                srand((int)time(0) + h * w - h);
                int random = (rand() % TIPO_AZULEJOS);//número random entre 0 y en numero de tipos de azulejo que hay
                int dezplazarVertical = random * TAM_AZULEJOS;

                va[verticeActual + 0].texCoords = 
                    Vector2f(0,0 + dezplazarVertical);
                va[verticeActual + 1].texCoords = 
                    Vector2f(TAM_AZULEJOS,0 + dezplazarVertical);
                va[verticeActual + 2].texCoords = 
                    Vector2f(TAM_AZULEJOS,TAM_AZULEJOS + dezplazarVertical);
                va[verticeActual + 3].texCoords = 
                    Vector2f(0,TAM_AZULEJOS + dezplazarVertical);
            }
            
            //nos adelantamos para tratar los siguientes 4 vertices
            verticeActual += VERTICES;
        }
    }

    return TAM_AZULEJOS;

}