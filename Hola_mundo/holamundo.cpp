#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
  RenderWindow ventana(VideoMode(800,600),"Hola mundo");
  CircleShape figura(100.f);
  figura.setFillColor(Color::Blue);
  
  while(ventana.isOpen())
  {
    Event evento;
  
    while(ventana.pollEvent(evento))
      if(evento.type == Event::Closed)
        ventana.close();

    ventana.clear();
    ventana.draw(figura);
    ventana.display();
  }
    

  return 0;
}
