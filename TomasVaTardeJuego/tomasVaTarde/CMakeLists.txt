cmake_minimum_required(VERSION 3.13)
project(tomasVaTarde)

set(CMAKE_CXX_STANDARD 14)

add_executable(tomasVaTarde main.cpp SoporteTextura.cpp SoporteTextura.hpp Motor.cpp Motor.hpp procesar_entradas.cpp actualizar.cpp dibujar.cpp PersonajeJugable.cpp PersonajeJugable.hpp Tomas.cpp Tomas.hpp Bob.cpp Bob.hpp AdministradorDeNiveles.cpp AdministradorDeNiveles.hpp cargar_nivel.cpp detectar_colisiones.cpp AdministradorDeSonido.cpp AdministradorDeSonido.hpp poblar_emisores.cpp Hud.cpp Hud.hpp Particula.cpp Particula.hpp SistemaDeParticulas.cpp SistemaDeParticulas.hpp reiniciarNivel.cpp)
target_link_libraries(tomasVaTarde sfml-graphics sfml-system sfml-audio sfml-window)