PROGS=main

all: $(PROGS)

main: main.o Compteur.o
		g++ -o $@ $^ -lSDL2 -g

main.o: main.cpp Graphique.hpp Jeu.hpp Oiseau.h Environnement.hpp Obstacle.h
		g++ -c $< -lSDL2 -g

Compteur.o: Compteur.cpp Compteur.hpp
	 	g++ -c $< -lSDL2 -g



clean:
		rm -f *.o *~ $(PROGS)
