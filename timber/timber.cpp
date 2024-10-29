/*
 * =====================================================================================
 *
 *       Filename:  timber.cpp
 *
 *    Description:  Archivo principal para el juego timber
 *
 *        Version:  1.0
 *        Created:  06/14/2019 08:07:31 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Carlos Miguel Correa Medina(basado en curso de udemy)
 *   Organization:  
 *
 * =====================================================================================
 */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

using namespace std;
using namespace sf;
const int num_ramas = 6;
Sprite ramas[num_ramas];
enum class lugar{IZQ,DER,NONE};
lugar poisicion_ramas[num_ramas];

void actualizarRamas(int semilla);
void moverNube(Sprite &nube,bool &activo,float &velocidad,Time tiempo,int variacion);

int main()
{
	//creando un objeto de tipo video
	VideoMode vm(1920,1080);

	RenderWindow ventana(vm,"¡¡Madera!!");

	//agregamos el background
	//cargamos el gráfico dentro de la textura
	Texture texturaBackground;
	texturaBackground.loadFromFile("gráficos/background.png");
	Sprite spriteBackground;
	spriteBackground.setTexture(texturaBackground);
	spriteBackground.setPosition(0,0);

	//Agregamos el arbol
	Texture texturaArbol;
	texturaArbol.loadFromFile("gráficos/arbol.png");
	Sprite spriteArbol;
	spriteArbol.setTexture(texturaArbol);
	spriteArbol.setPosition(810,0);


	//Agregamos a la abeja
	Texture texturaAbeja;
	texturaAbeja.loadFromFile("gráficos/insecto.png");
	Sprite spriteAbeja;
	spriteAbeja.setTexture(texturaAbeja);
	spriteAbeja.setPosition(800,800);

	bool Abjea_activa = false;

	float velocidad_abeja = 0.0f;

	//agregamos 3 nubes con la misma textura.
	Texture texturaNube;
	texturaNube.loadFromFile("gráficos/nube.png");
	//3 nubes
	Sprite sp_nube1;
	Sprite sp_nube2;
	Sprite sp_nube3;
	sp_nube1.setTexture(texturaNube);
	sp_nube2.setTexture(texturaNube);
	sp_nube3.setTexture(texturaNube);
	//posicionamos a las tres nubes
	sp_nube1.setPosition(0,0);
	sp_nube2.setPosition(0,250);
	sp_nube3.setPosition(0,500);
	
	bool nube1_activo = false;
	bool nube2_activo = false;
	bool nube3_activo = false;

	float velocidad_nube1 = 0.0f;
	float velocidad_nube2 = 0.0f;
	float velocidad_nube3 = 0.0f;

	Clock reloj;
	RectangleShape barratiempo;
	float Anchobarratiempo = 400;
	float Altobarratiempo = 80;
	barratiempo.setSize(Vector2f(Anchobarratiempo,Altobarratiempo));
	barratiempo.setFillColor(Color::Red);
	barratiempo.setPosition((1920/2) - Anchobarratiempo/2, 980);

	Time tiempoTotalJuego;
	float tiempoRestante = 6.0f;
	float Anchobarraporsegundo = Anchobarratiempo / tiempoRestante;


	bool pausa = true;
	//Manejo de texto a mostrar en pantalla

	int puntuacion = 0;
	Text mensaje;
	Text marcador;
	//Cargamos la fuente
	Font fuente;
	fuente.loadFromFile("fuentes/acut.ttf");
	mensaje.setFont(fuente);
	marcador.setFont(fuente);
	//asignar mensaje
	mensaje.setString("Presione la Tecla Enter para empezar");
	marcador.setString("Puntos = 0");
	//ajustando el tamaño
	mensaje.setCharacterSize(75);
	marcador.setCharacterSize(100);
	//Ponemos un color
	Color blanco = Color::White;
	mensaje.setFillColor(blanco);
	marcador.setFillColor(blanco);
	//agregamos el texto a la pantalla
	FloatRect textoDin = mensaje.getLocalBounds();
	mensaje.setOrigin
		(
			textoDin.left + textoDin.width / 2.0f,
			textoDin.top + textoDin.height / 2.0f
		);
	mensaje.setPosition(1920/2.0f , 1080/2.0f);
	marcador.setPosition(20,20);

	//preparamos 6 ramas
	Texture texturaRama;
	texturaRama.loadFromFile("gráficos/rama.png");
	//aplicamos la textura a las 6 ramas
	for(int i = 0; i < num_ramas; i++)
	{
		ramas[i].setTexture(texturaRama);
		ramas[i].setPosition(-2000,-2000);
		ramas[i].setOrigin(220,20);
	}
	//preparamos al juagador
	Texture texJugador;
	texJugador.loadFromFile("gráficos/jugador.png");
	Sprite sp_jugador;
	sp_jugador.setTexture(texJugador);
	sp_jugador.setPosition(580,720); 
	//el jugador empieza en el lado izquierdo 
	lugar lado_jugador = lugar::IZQ;

	//preparamos la lapida
	Texture texLapida;
	texLapida.loadFromFile("gráficos/lapida.png");
	Sprite sp_lapida;
	sp_lapida.setTexture(texLapida);
	sp_lapida.setPosition(600,860);

	//preparamos la hacha
	Texture texHacha;
	texHacha.loadFromFile("gráficos/hacha.png");
	Sprite sp_hacha;
	sp_hacha.setTexture(texHacha);
	sp_hacha.setPosition(700,830);

	//alineamos la hacha con el árbol
	const float POSICION_IZQ_HACHA = 700;
	const float POSICION_DER_HACHA = 1075;

	//preparamos el registro de vuelo
	Texture texLog;
	texLog.loadFromFile("gráficos/log.png");
	Sprite sp_log;
	sp_log.setTexture(texLog);
	sp_log.setPosition(810,720);

	//variable utiles para el registro de vuelo
	bool logActivo = false;
	float velocidadLogx = 1000;
	float velocidadLogy = -1500;


	//actualizamos las ramas
	actualizarRamas(1);
	actualizarRamas(2);
	actualizarRamas(3);
	actualizarRamas(4);
	actualizarRamas(5);

	//controlar cuando puede precionar el jugador botones
	bool aceptar_input = false;
	//preparamos el sonido
	SoundBuffer cortarBuffer;
	cortarBuffer.loadFromFile("sonido/cortar.wav");
	Sound cortar;
	cortar.setBuffer(cortarBuffer);

	SoundBuffer muerteBuffer;
	muerteBuffer.loadFromFile("sonido/muerte.wav");
	Sound muerte;
	muerte.setBuffer(muerteBuffer);

	SoundBuffer tiempoFueraBuffer;
	tiempoFueraBuffer.loadFromFile("sonido/tiempo_fuera.wav");
	Sound tiempo_fuera;
	tiempo_fuera.setBuffer(tiempoFueraBuffer);

	//ciclo principal del juego
	while(ventana.isOpen())
	{
		if(Keyboard::isKeyPressed(Keyboard::Escape))
			ventana.close();
		
		Event evento;
		while(ventana.pollEvent(evento))
		{
			if(evento.type == Event::KeyReleased && !pausa)
			{
				aceptar_input = true;
				//esconder hacha
				sp_hacha.setPosition(2000,sp_hacha.getPosition().y);
			}
		}
		//empezar el juego
		if(Keyboard::isKeyPressed(Keyboard::Return))
		{ 
			pausa = false; 
			//reiniciar el tiempo  y el marcador
			puntuacion = 0;
			tiempoRestante = 6;
			//hacemos que las ramas desaparezcan.
			for(int i = 0; i < num_ramas; i++)			
				poisicion_ramas[i] = lugar::NONE;
			
			//escondemos la lapida (la colocamos afuera del rango de la pantalla)
			sp_lapida.setPosition(700,3000);

			//colocamos al jugador en posición
			sp_jugador.setPosition(580,720);
			aceptar_input = true;
		}
		
		if(aceptar_input)
		{
			if(Keyboard::isKeyPressed(Keyboard::Right))
			{
				//poner al jugador del lado derecho
				lado_jugador = lugar::DER;
				puntuacion++;
				//añadir el total de tiempo faltante
				//(esta formula se puede modificar para cambiar la dificultad)
				tiempoRestante += (2 / puntuacion) + .15;

				sp_hacha.setPosition(POSICION_DER_HACHA,sp_hacha.getPosition().y);
				sp_jugador.setPosition(POSICION_DER_HACHA,sp_jugador.getPosition().y);

				actualizarRamas(puntuacion);
				//poner el registro de vuelo a la izquierda
				sp_log.setPosition(810,720);
				velocidadLogx = -5000;
				logActivo = true;
				aceptar_input = false;

				cortar.play();
			}

			if(Keyboard::isKeyPressed(Keyboard::Left))
			{
				//poner al jugador del lado derecho
				lado_jugador = lugar::IZQ;
				puntuacion++;
				//añadir el total de tiempo faltante
				//(esta formula se puede modificar para cambiar la dificultad)
				tiempoRestante += (2 / puntuacion) + .15;

				sp_hacha.setPosition(POSICION_IZQ_HACHA,sp_hacha.getPosition().y);
				sp_jugador.setPosition(POSICION_IZQ_HACHA,sp_jugador.getPosition().y);

				actualizarRamas(puntuacion);
				//poner el registro de vuelo a la izquierda
				sp_log.setPosition(810,720);
				velocidadLogx = 5000;
				logActivo = true;
				aceptar_input = false;
				cortar.play();
			}
		}


		//si pausa es falsa entonces movemos los objetos en el programa
		if(!pausa)
		{
			//Medimos el tiempo en cada marco
			Time dt = reloj.restart();
			tiempoRestante -= dt.asSeconds();
			//estimar tamañó de de la barra de tiempo.
			barratiempo.setSize(Vector2f(Anchobarraporsegundo * tiempoRestante, Altobarratiempo));

			// si te pasas del tiempo
			if(tiempoRestante <= 0.0f)
			{
				pausa = true;

				mensaje.setString("!!!Se acabo el tiempo!!!");
				//re posicionar el mensaje por el tamaño del texto
				FloatRect textoDin = mensaje.getLocalBounds();
				mensaje.setOrigin
					(
						textoDin.left + textoDin.width/2.0f,
						textoDin.top + textoDin.height/2.0f
					);
				mensaje.setPosition(1920/2.0f , 1080/2.0f);
				tiempo_fuera.play();
			}
			//Configuración de abeja
			if(!Abjea_activa)
			{
				srand((int)time(0) * 10);
				velocidad_abeja = (rand() % 200) + 200;

				//altura de la abeja
				srand((int)time(0) * 10);
				float altura = (rand() % 500 ) + 500;
				spriteAbeja.setPosition(0,altura);
				Abjea_activa = true;
			}
			else
			{
				spriteAbeja.setPosition
				(
					spriteAbeja.getPosition().x + (velocidad_abeja * dt.asSeconds()),
					spriteAbeja.getPosition().y 
				);

				//ha la abeja alcanzado el borde derecho de la pantalla
			if(spriteAbeja.getPosition().x > 2000)
				Abjea_activa = false;
			}
			//movemos las nubes
			moverNube(sp_nube1,nube1_activo,velocidad_nube1,dt,1);
			moverNube(sp_nube2,nube2_activo,velocidad_nube2,dt,2);
			moverNube(sp_nube3,nube3_activo,velocidad_nube3,dt,3);

			//actualizamos  el marcador
			stringstream ss;
			ss << "Puntos = " << puntuacion;
			marcador.setString(ss.str());

			//actualizamos las ramas
			for (int i = 0; i < num_ramas; i++)
			{
				float altura = i * 150;
				if(poisicion_ramas[i] == lugar::IZQ)
				{
					//movemos la rama hacia la izquierda
					ramas[i].setPosition(610,altura);
					//damos la vuelta a la rama 180 grados hacia el otro lado
					ramas[i].setRotation(180);
				}
				else if(poisicion_ramas[i] == lugar::DER)
				{
					//movemos la rama hacia la derecha
					ramas[i].setPosition(1330,altura);
					//dejamos la rama en la posicion inicial
					ramas[i].setRotation(0);
				}
				else
				{
					//escondemos la rama
					ramas[i].setPosition(3000,altura);
				}
				
			}
			//manejar los registros de vuelo
			if(logActivo)
			{
				sp_log.setPosition
					(
						sp_log.getPosition().x + (velocidadLogx *  dt.asSeconds()),
						sp_log.getPosition().y + (velocidadLogy * dt.asSeconds())
					);
				//tiene el registro alcanzado el borde derecho?
				if(sp_log.getPosition().x < -100 || sp_log.getPosition().y > 2000)
				{
					logActivo = false;
					sp_log.setPosition(810,720);
				}
			}

			//El jugador ha muerto
			if(poisicion_ramas[5] == lado_jugador)
			{
				pausa = true;
				aceptar_input = false;

				//mostramos la lapida
				sp_lapida.setPosition(sp_jugador.getPosition().x,sp_jugador.getPosition().y);
				//escondemos al jugador
				sp_jugador.setPosition(2000,3000);
				//cambiamos el mensaje en pantalla
				mensaje.setString("!!!MORISTE!!!");
				//centramos en la pantalla
				FloatRect textoReact = mensaje.getLocalBounds();
				mensaje.setOrigin
					(
						textoReact.left + textoReact.width / 2.0f, 
						textoReact.top = textoReact.height / 2.0f
					);
				
				mensaje.setPosition(1920 / 2.0f , 1080 / 2.0f);
				muerte.play();
			}
		}//final de if de pausa


		ventana.clear();
		//dibujamos los objetos en la ventana
		ventana.draw(spriteBackground);
		ventana.draw(spriteAbeja);
		ventana.draw(spriteArbol);
		ventana.draw(sp_nube1);
		ventana.draw(sp_nube2);
		ventana.draw(sp_nube3);
		ventana.draw(marcador);
		ventana.draw(barratiempo);
		if(pausa)
			ventana.draw(mensaje);

		//dibujamos las ramas
		for(int i = 0; i < num_ramas; i++)
			ventana.draw(ramas[i]);

		ventana.draw(sp_jugador);
		ventana.draw(sp_lapida);
		ventana.draw(sp_log);
		ventana.draw(sp_hacha);

		ventana.display();
	}
	
	return 0;
}

void moverNube(Sprite &nube,bool &activo,float &velocidad,Time tiempo,int variacion)
{
	if(!activo)
	{
		srand((int)time(0) * 10*variacion);
		velocidad = (rand() % 200);
		//altura de la nube
		srand((int)time(0) * 10*variacion);
		float altura = (rand() % 150*variacion) - 20*variacion;
		nube.setPosition(1920,altura);
		activo = true;
	}
	else
	{
		nube.setPosition
		(
			nube.getPosition().x - (velocidad * tiempo.asSeconds()),
			nube.getPosition().y
		);
		if(nube.getPosition().x < -200)
			activo = false;

	}

}
void actualizarRamas(int semilla)
{
	//movemos todas las ramas una posición abajo
	for (int j = num_ramas -1; j > 0; j--)
		poisicion_ramas[j] = poisicion_ramas[j - 1];
	//creamos una nueva rama en la posición 0
	srand((int)time(0) + semilla);
	int r = (rand() % 5);
	
	switch(r)
	{
		case 0:
			poisicion_ramas[0] = lugar::IZQ;
			break;
		case 1:
			poisicion_ramas[0] = lugar::DER;
			break;
		
		default:
			poisicion_ramas[0] = lugar::NONE;
			break;
	}

}