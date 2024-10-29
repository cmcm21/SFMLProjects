SFML=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

ejecutable: timber.o
	g++ timber.o -o ejecutable $(SFML)

timber.o: timber.cpp
	g++ timber.cpp -c