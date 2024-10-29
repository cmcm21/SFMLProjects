//
// Created by senpai on 7/22/19.
//
#include <SFML/Audio.hpp>
#include "SoporteTextura.hpp"
#include <sstream>
#include <fstream>
#include "AdministradorDeNiveles.hpp"


int **AdministradorDeNiveles::siguienteNivel(sf::VertexArray &nivelVA)
{
    tamNivel.x = 0;
    tamNivel.y = 0;

    nivelActual++;
    if(nivelActual > numNiveles)
    {
        nivelActual = 1;
        modificadorDeTiempo -= 0.1f;
    }

    std::string cargarNivel;

    switch (nivelActual)
    {
        case 1:
            cargarNivel = "../niveles/nivel1.txt";
            posicionInicial.x = 100;
            posicionInicial.y = 100;
            limiteDeTiempoBase = 30.0f;
            break;

        case 2:
            cargarNivel = "../niveles/nivel2.txt";
            posicionInicial.x = 50;
            posicionInicial.y = 200;
            limiteDeTiempoBase = 50.0f;
            break;

        case 3:
            cargarNivel = "../niveles/nivel3.txt";
            posicionInicial.x = 1250;
            posicionInicial.y = 0;
            limiteDeTiempoBase = 30.0f;
            break;

        case 4:
            cargarNivel = "../niveles/nivel4.txt";
            posicionInicial.x = 100;
            posicionInicial.y = 3600;
            limiteDeTiempoBase = 100.0f;
            break;
    }//fin de switch

    std::ifstream archivoEntrada(cargarNivel);
    std::string linea;

    while(std::getline(archivoEntrada,linea))
        ++tamNivel.y;

    tamNivel.x = static_cast<int>(linea.length());
    //regresamos al inicio del archivo
    archivoEntrada.clear();
    archivoEntrada.seekg(0,std::ios::beg);

    //preparamos arreglo para contener el escenario del nivel (enteros)
    int **matrizNivel = new int *[tamNivel.y];
    for(int i = 0; i < tamNivel.y; i++)
        matrizNivel[i] = new int[tamNivel.x];

    std::string fila;
    int j = 0;
    while(archivoEntrada >> fila)
    {
        for(int i = 0; i < fila.length(); i++)
        {
            const char valor = fila[i];
            matrizNivel[j][i] = atoi(&valor); // lo pasamos de caracter a entero
        }
        j++;
    }

    archivoEntrada.close();

    nivelVA.setPrimitiveType(sf::Quads);
    nivelVA.resize(tamNivel.x * tamNivel.y * VERTICES);
    int verticeActual = 0;

    for(int x = 0; x < tamNivel.x; x++)
    {
        for(int y = 0 ; y < tamNivel.y; y++)
        {
            //vertice izquierdo superior
            nivelVA[verticeActual + 0].position = sf::Vector2f(x * TAM_AZULEJO , y * TAM_AZULEJO);
            //vertice derecho superior
            nivelVA[verticeActual + 1].position = sf::Vector2f((x * TAM_AZULEJO) + TAM_AZULEJO,y * TAM_AZULEJO);
            //vertice derecho inferior
            nivelVA[verticeActual + 2].position =
                    sf::Vector2f((x * TAM_AZULEJO) + TAM_AZULEJO, (y * TAM_AZULEJO) + TAM_AZULEJO);
            //vertice izquierdo inferior
            nivelVA[verticeActual + 3].position =
                    sf::Vector2f(x * TAM_AZULEJO,(y * TAM_AZULEJO) + TAM_AZULEJO);

            //manejo de texturas
            //el dezplazamiento que se hara en las coordenadas para saber que textura ocupar
            //0 (aire), 1(planicie), 2(agua), 3(fuego), 4(nivel completado)
            //estos numeros se guardaron del archivo de nivel leído
            int dezplazamiento = matrizNivel[y][x] * TAM_AZULEJO;
            //la imagen de texturas se recorre en el eje y

            //vertice de pixel izquierdo superior
            nivelVA[verticeActual + 0].texCoords = sf::Vector2f(0,0 + dezplazamiento);
            //vertice de pixel derecho superior
            nivelVA[verticeActual + 1].texCoords = sf::Vector2f(TAM_AZULEJO,0 + dezplazamiento);
            //vertice de pixel derecho inferior
            nivelVA[verticeActual + 2].texCoords =
                    sf::Vector2f(TAM_AZULEJO,0 + dezplazamiento + TAM_AZULEJO);
            //vertice de pixel izquierdo inferior
            nivelVA[verticeActual + 3].texCoords =
                    sf::Vector2f(0,0 + dezplazamiento + TAM_AZULEJO);

            verticeActual += VERTICES;
        }
    }
    return matrizNivel;
}

sf::Vector2i AdministradorDeNiveles::getTamNivel()
{
    return tamNivel;
}

int AdministradorDeNiveles::getNivelActual()
{
    return nivelActual;
}
float AdministradorDeNiveles::getLimiteDeTiempo()
{
    return limiteDeTiempoBase * modificadorDeTiempo;
}
sf::Vector2f AdministradorDeNiveles::getPosicionInicial()
{
    return posicionInicial;
}

void AdministradorDeNiveles::setNivelActual(int nivel)
{
    this->nivelActual = nivel;
}
