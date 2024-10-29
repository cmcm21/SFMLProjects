#include "Jugador.hpp"
#include "Arena.hpp"
#include "SoporteTextura.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Bala.hpp"
#include <sstream>
#include <fstream>
#include "Item.hpp"

using namespace sf;
using namespace std;

int main()
{
    SoporteTextura soporte;
    const std::string archivo = "datosJuego/registroDePuntuaciones.txt";
    //el juego siempre se va a encontrar en algun de estos estados
    enum class Estado
    {
        PAUSA,SUBIENDO_NIVEL,JUEGO_TERMINADO,CORRIENDO 
    };
    Estado estado = Estado::JUEGO_TERMINADO;

    //obtener el tamaño de la pantalla y crear una ventana SFML
    Vector2f resolucion;
    resolucion.x = VideoMode::getDesktopMode().width;
    resolucion.y = VideoMode::getDesktopMode().height;
     
    RenderWindow ventana(VideoMode(resolucion.x, resolucion.y),"Arena Zombie",Style::Fullscreen );

    //creamos una ventana para la acción principal
    View VistaPrincipal(FloatRect(0,0,resolucion.x,resolucion.y));

    //reloj para cronometrar todo el juego
    Clock reloj;
    //reloj para el total de tiempo de un estado
    Time tiempoTotal;

    //coordenadas del mouse Fisico
    Vector2f posicionMouseFisico;
    //coordenadas del mouse en pantalla
    Vector2i posicionMousePantalla;

    Jugador jugador;

    IntRect arena;

    VertexArray fondoPantalla;
    Texture texturaFondo = SoporteTextura::getTextura("gráficos/background_sheet.png");

    int numZombies;
    int numZombiesVivos;
    Zombie *zombies = nullptr;

    // manejo de balas
    Bala balas[100];
    int balaActual = 0;
    int balasRepuesto = 24;
    int balasEnCartucho = 6;
    int tamCartucho = 6;
    int rangoDisparo = 1; // cuantas balas se disparan

    //cuando fue la ultima vez que se presiono el botón para disparar
    Time ultimoDisparo;
    
    //reemplazar el mouse por una mira
    ventana.setMouseCursorVisible(false);
    Sprite sp_mira;
    Texture texturaMira = SoporteTextura::getTextura("gráficos/mira.png");

    sp_mira.setTexture(texturaMira);
    sp_mira.setOrigin(25,25);

    Item vidaItem(1);
    Item municionItem(2);

    int puntuacion = 0;
    int puntuacionMasAlta = 0;

    //texto que se muestra en pantalla
    Sprite sp_finDeJuego;
    Texture texFinDeJuego = SoporteTextura::getTextura("gráficos/background.png");
    sp_finDeJuego.setTexture(texFinDeJuego);
    sp_finDeJuego.setPosition(0,0);
    
    //creamos una vista para el HUD
    View vistaHud (sf::FloatRect(0,0,resolucion.x, resolucion.y));

    //sprite para el icono de munición
    Sprite sp_iconMuncion;
    Texture texIconMucion = SoporteTextura::getTextura("gráficos/municion_icon.png");
    sp_iconMuncion.setTexture(texIconMucion);
    sp_iconMuncion.setPosition(128,980);

    Font fuente;
    fuente.loadFromFile("fuente/zombiecontrol.ttf");

    //texto de pausa
    Text textoPausa;
    textoPausa.setFont(fuente);
    textoPausa.setCharacterSize(68);
    textoPausa.setFillColor(Color::White);
    textoPausa.setPosition(650,560);
    textoPausa.setString("Presione Enter \n para continuar");

    //texto de juego terminado
    Text textoFinJuego;
    textoFinJuego.setFillColor(Color::White);
    textoFinJuego.setFont(fuente);
    textoFinJuego.setCharacterSize(80);
    textoFinJuego.setPosition(480,900);
    textoFinJuego.setString("Presiona Enter para Jugar");

    //texto al subir de nivel
    Text subiendoNivel;
    subiendoNivel.setFont(fuente);
    subiendoNivel.setCharacterSize(60);
    subiendoNivel.setFillColor(Color::White);
    subiendoNivel.setPosition(180,510);
    std::stringstream ssNivel;
    ssNivel << 
        "1- Aumentando frecuencia de disparo" <<
        "\n2- Aumentando espacio de cartucho(siguiente recarga)" <<
        "\n3- Aumentando vida maxima" <<
        "\n4- Aumentando velociadad del Jugador" <<
        "\n5- Mas y mejores items de vida" <<
        "\n6- Mas y mejores items de municion"<<
        "\n7- Salir y guardar";
    subiendoNivel.setString(ssNivel.str());

    //texto munición
    Text textoMunicion;
    textoMunicion.setFont(fuente);
    textoMunicion.setCharacterSize(50);
    textoMunicion.setFillColor(Color::White);
    textoMunicion.setPosition(0,980);
    //texto recarga
    Text textoRecarga;
    textoRecarga.setFont(fuente);
    textoRecarga.setCharacterSize(50);
    textoRecarga.setFillColor(Color::White);
    textoRecarga.setPosition(0,680);
    std::stringstream ssRecarga;
    ssRecarga << "Presione 'R' \n para recargar";
    textoRecarga.setString(ssRecarga.str());

    //texto de puntucion
    Text textoPuntuacion;
    textoPuntuacion.setFont(fuente);
    textoPuntuacion.setCharacterSize(50);
    textoPuntuacion.setFillColor(Color::White);
    textoPuntuacion.setPosition(20,0);


    std::ifstream leer(archivo);
    if(leer.is_open())
    {
        leer >> puntuacionMasAlta;
        leer.close();
    }


    //texto de puntuacion más alta
    Text textoPuntuacionMasAlta;
    textoPuntuacionMasAlta.setFont(fuente);
    textoPuntuacionMasAlta.setFillColor(Color::White);
    textoPuntuacionMasAlta.setCharacterSize(50);
    textoPuntuacionMasAlta.setPosition(1380,0);
    std::stringstream s;
    s << "Mejor Puntuacion:" << puntuacionMasAlta;
    textoPuntuacionMasAlta.setString(s.str());

    //zombies restantes
    Text textoZombiesRes;
    textoZombiesRes.setFont(fuente);
    textoZombiesRes.setCharacterSize(50);
    textoZombiesRes.setFillColor(Color::White);
    textoZombiesRes.setPosition(1675,980);
    textoZombiesRes.setString("Zombies: 100");

    int oleada = 0;
    Text texOleada;
    texOleada.setFont(fuente);
    texOleada.setCharacterSize(50);
    texOleada.setFillColor(Color::White);
    texOleada.setPosition(1300,980);
    texOleada.setString("Oleada: 0");

    //texto de vida
    RectangleShape barraVida;
    barraVida.setFillColor(Color::Red);
    barraVida.setPosition(500,980);

    //cuando  se realizo la ultima actualización
    int desdeUltimoFrameDeHudActualizado = 0;
    //frecuencia de actualización del HUD
    int fpsHud = 1000;

    //manejo de audio
    SoundBuffer golpeBuffer;
    golpeBuffer.loadFromFile("sonidos/golpe.wav");
    Sound golpe;
    golpe.setBuffer(golpeBuffer);

    SoundBuffer salpicarBuffer;
    salpicarBuffer.loadFromFile("sonidos/salpicar.wav");
    Sound salpicar;
    salpicar.setBuffer(salpicarBuffer);

    SoundBuffer disparoBuffer;
    disparoBuffer.loadFromFile("sonidos/disparo.wav");
    Sound disparo;
    disparo.setBuffer(disparoBuffer);

    SoundBuffer recargaBuffer;
    recargaBuffer.loadFromFile("sonidos/recarga.wav");
    Sound recarga;
    recarga.setBuffer(recargaBuffer);

    SoundBuffer recargaFallidaBuffer;
    recargaFallidaBuffer.loadFromFile("sonidos/recarga_fallida.wav");
    Sound recargaFallida;
    recargaFallida.setBuffer(recargaFallidaBuffer);

    SoundBuffer powerUpBuffer;
    powerUpBuffer.loadFromFile("sonidos/powerup.wav");
    Sound powerUp;
    powerUp.setBuffer(powerUpBuffer);

    SoundBuffer recogerBuffer;
    recogerBuffer.loadFromFile("sonidos/recoger.wav");
    Sound recoger;
    recoger.setBuffer(recogerBuffer);

    int aumentoArena;
    while(ventana.isOpen())
    {
        Event evento;
        while(ventana.pollEvent(evento))
        {
            if(evento.type == Event::KeyPressed)
            {
                //manejo de pausa en el juego
                if(evento.key.code == Keyboard::Return && estado == Estado::CORRIENDO)
                {
                    estado = Estado::PAUSA;
                }
                else if(evento.key.code == Keyboard::Return && estado == Estado::PAUSA)
                {
                    estado = Estado::CORRIENDO;
                    reloj.restart();
                }
                //empezar un nuevo juego mientras se esta en estado JUEGO_TERMINADO
                else if(evento.key.code == Keyboard::Return && estado == Estado::JUEGO_TERMINADO)   
                {
                    estado = Estado::SUBIENDO_NIVEL;
                    oleada = 0;
                    puntuacion = 0;
                    //preparamos la municion la pistola para la siguiente oleada
                    balaActual = 0;
                    balasRepuesto = 24;
                    balasEnCartucho = 6;
                    tamCartucho = 6;
                    rangoDisparo = 1;
                    jugador.recetearJugador();

                }

                if(estado == Estado::CORRIENDO)
                {
                    //recarga
                    if(evento.key.code == Keyboard::R)
                    {
                        if(balasRepuesto >= tamCartucho)
                        {
                            balasEnCartucho = tamCartucho;
                            balasRepuesto -= tamCartucho;
                            recarga.play();
                        }
                        else if(balasRepuesto > 0)
                        {
                            balasEnCartucho = balasRepuesto;
                            balasRepuesto = 0;
                            recarga.play();
                        }
                        else
                        {
                            recargaFallida.play();
                        }
                    }
                }
            }
           
            
        }//termina while de eventos
        if(Keyboard::isKeyPressed(Keyboard::Escape))
            ventana.close();
    
        //manejar controles mientras se juega
        if(estado == Estado::CORRIENDO)
        {
            if(Keyboard::isKeyPressed(Keyboard::W))
                jugador.moverArriba();
            else
                jugador.pararArriba();
            if(Keyboard::isKeyPressed(Keyboard::D))
                jugador.moverDerecha();
            else
                jugador.pararDerecha();
            if(Keyboard::isKeyPressed(Keyboard::S))
                jugador.moverAbajo();
            else
                jugador.pararAbajo();
            if(Keyboard::isKeyPressed(Keyboard::A))
                jugador.moverIzquierda();
            else
                jugador.pararIzquierda();

            //manejamos el disparo
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                if(tiempoTotal.asMilliseconds() - ultimoDisparo.asMilliseconds() > 1000/rangoDisparo
                    && balasEnCartucho > 0)
                {
                    balas[balaActual].disparar(jugador.getCentro().x,jugador.getCentro().y,
                        posicionMouseFisico.x,posicionMouseFisico.y);

                    balaActual++;
                    if(balaActual > 99)
                        balaActual = 0;

                    ultimoDisparo = tiempoTotal;
                    disparo.play();
                    balasEnCartucho--;
                }
            }
        }
            
        if(estado == Estado::SUBIENDO_NIVEL)
        {
            switch(evento.key.code)
            {
                case Keyboard::Num1:
                    rangoDisparo++;
                    estado = Estado::CORRIENDO;
                    break;
                case Keyboard::Num2:
                    tamCartucho += tamCartucho;
                    estado = Estado::CORRIENDO;
                    break;
                case Keyboard::Num3:
                    jugador.aumentarVida();
                    estado = Estado::CORRIENDO;
                    break;
                case Keyboard::Num4:
                    jugador.aumentarVelocidad();
                    estado = Estado::CORRIENDO;
                    break;
                case Keyboard::Num5:
                    vidaItem.mejorar();
                    estado = Estado::CORRIENDO;
                    break;
                case Keyboard::Num6:
                    municionItem.mejorar();
                    estado = Estado::CORRIENDO;
                    break;
                case Keyboard::Num7:
                    estado = Estado::JUEGO_TERMINADO;
            }
           
            if(estado == Estado::CORRIENDO)
            {
                oleada++;
                //preparamos el nivel
                aumentoArena = oleada * 100;
                arena.width = 500 + aumentoArena;
                arena.height = 500 + aumentoArena;
                arena.left = 0;
                arena.top = 0;

                int tamAzulejo = crearFondo(fondoPantalla,arena);

                jugador.engendrar(arena,resolucion,tamAzulejo);
                //configuramos los items
                vidaItem.setArea(arena);
                municionItem.setArea(arena);

                numZombies = 5 * oleada;
                //limipiamos la memoria por si hay algo guardado
                delete[] zombies;
                zombies = crearHorda(numZombies,arena);
                numZombiesVivos = numZombies;

                powerUp.play();
                reloj.restart();
            }

        }
        //actualización pantalla
        if(estado == Estado::CORRIENDO)
        {
            Time dt = reloj.restart();
            tiempoTotal += dt;
            float dtSegundos = dt.asSeconds();

            posicionMousePantalla = Mouse::getPosition();
            posicionMouseFisico = ventana.mapPixelToCoords(Mouse::getPosition(),VistaPrincipal);

            sp_mira.setPosition(posicionMouseFisico);

            jugador.actualizar(dtSegundos,Mouse::getPosition());

            Vector2f posicionJugador(jugador.getCentro());

            VistaPrincipal.setCenter(jugador.getCentro());
            
            for(int i = 0; i < numZombies; i++)
                if(zombies[i].estaVivo())
                    zombies[i].actualizar(dtSegundos,posicionJugador);
            
            for(int i = 0; i < 100; i++)
                if(balas[i].estaVolando())
                    balas[i].actualizar(dtSegundos);

            vidaItem.actualizar(dt.asSeconds());
            municionItem.actualizar(dtSegundos);

            //detección de colisiones
            //disparos a zombies
            for(int i = 0; i < 100; i++)
            {
                for(int j = 0; j < numZombies; j++)
                {
                    if(balas[i].estaVolando() && zombies[j].estaVivo())           
                    {
                        if(balas[i].getPosicion().intersects(zombies[j].getPosicion()))
                        {
                            balas[i].parar();

                            //verificamos si matamos al zombie
                            if(zombies[j].impacto())
                            {
                                puntuacion += 10;
                                if(puntuacion > puntuacionMasAlta)
                                    puntuacionMasAlta = puntuacion;

                                numZombiesVivos--;

                                //si matamos a todos los zombies cambiamos de nivel
                                if(numZombiesVivos == 0)
                                    estado = Estado::SUBIENDO_NIVEL;
                            }
                            salpicar.play();
                        }
                    }
                }
            }//for para detectar colisiones de disparos

            //colisión de zombies con jugador
            for(int i = 0; i < numZombies; i++)
            {
                if(jugador.getPosicion().intersects(zombies[i].getPosicion()) && 
                zombies[i].estaVivo())
                {
                    if(jugador.golpear(tiempoTotal))
                    {                        
                        golpe.play();
                    }
                    else if(jugador.getVida() <= 0)
                    {
                        estado = Estado::JUEGO_TERMINADO;
                    }
                    
                }
            }//termina colisión con zombies
            
            //colisión con items
            if(jugador.getPosicion().intersects(vidaItem.getPosicion()) && vidaItem.estaCreado())
            {
                jugador.incrementarNivelDeVida(vidaItem.cachar());
                recoger.play();
            }
            
            if(jugador.getPosicion().intersects(municionItem.getPosicion()) && municionItem.estaCreado())
            {
                balasRepuesto += municionItem.cachar();
                recarga.play();

            }

            //hud
            //le damos ala barra de vida un tamaño correspondiente a la vida del jugador
            barraVida.setSize(Vector2f(jugador.getVida() * 3,70));
            desdeUltimoFrameDeHudActualizado++;
            if(desdeUltimoFrameDeHudActualizado > fpsHud)
            {
                //actualizamos el hud
                std::stringstream ssMunicion;
                std::stringstream ssPuntuacion;
                std::stringstream ssPuntuacionMasAlta;
                std::stringstream ssOleada;
                std::stringstream ssZombiesVivos;

                //munición
                ssMunicion << balasEnCartucho << "/" << balasRepuesto;
                textoMunicion.setString(ssMunicion.str());

                //puntuación
                ssPuntuacion << "Puntos:" << puntuacion;
                textoPuntuacion.setString(ssPuntuacion.str());

                //puntuacion más alta
                ssPuntuacionMasAlta << "Mejor puntuacion:" <<puntuacionMasAlta;
                textoPuntuacionMasAlta.setString(ssPuntuacionMasAlta.str());

                //oleada
                ssOleada << "Ola:" << oleada;
                texOleada.setString(ssOleada.str());

                //zombies
                ssZombiesVivos << "Zombies:" << numZombiesVivos;
                textoZombiesRes.setString(ssZombiesVivos.str());

                desdeUltimoFrameDeHudActualizado = 0;
            }
        }
        //dibujamos 
        if(estado == Estado::CORRIENDO)
        {
            //el orden en el que se dibujan los sprites
            //es el orden en el que se veran las imaganes
            ventana.clear();

            ventana.setView(VistaPrincipal);

            ventana.draw(fondoPantalla,&texturaFondo);

            for(int i = 0; i < numZombies; i++)
                ventana.draw(zombies[i].getSprite());
            
            for(int i = 0; i < 100; i++)
                if(balas[i].estaVolando())
                    ventana.draw(balas[i].getForma()); 

            ventana.draw(jugador.getSprite());
            //dibujamos los items
            if(municionItem.estaCreado())
                ventana.draw(municionItem.getSprite());
            if(vidaItem.estaCreado())
                ventana.draw(vidaItem.getSprite());


            ventana.draw(sp_mira);
            ventana.setView(vistaHud);
            ventana.draw(textoRecarga);
            ventana.draw(sp_iconMuncion);
            ventana.draw(textoMunicion);
            ventana.draw(textoPuntuacion);
            ventana.draw(textoPuntuacionMasAlta);
            ventana.draw(barraVida);
            ventana.draw(texOleada);
            ventana.draw(textoZombiesRes);


          
        }
         if(estado == Estado::SUBIENDO_NIVEL)
        {
            ventana.draw(sp_finDeJuego);
            ventana.draw(subiendoNivel);
        }

        if(estado == Estado::PAUSA)
            ventana.draw(textoPausa);
            
        if(estado == Estado::JUEGO_TERMINADO)
        {
            std::ofstream escribir(archivo);
            escribir << puntuacionMasAlta;
            escribir.close();
            ventana.draw(sp_finDeJuego);
            ventana.draw(textoFinJuego);
            ventana.draw(textoPuntuacion);
            ventana.draw(textoPuntuacionMasAlta);
        }

        ventana.display();
    }//termina el while del juego

    delete[] zombies;
    return 0;
}