PROGS=main TestU_compteurs

all: $(PROGS)

main: main.o Graphique.o Compteur.o
		g++ -o $@ $^ -lSDL2 -g

TestU_compteurs: main_test.o Compteur.o
		g++ -o $@ $^ -lSDL2 -g

main.o: main.cpp Graphique.hpp Jeu.hpp Oiseau.h Environnement.hpp Obstacle.h Compteur.hpp
		g++ -c $< -lSDL2 -g

main_test.o: main_test.cpp Compteur.hpp
		g++ -c $< -lSDL2 -g

Graphique.o: Graphique.cpp Graphique.hpp
		g++ -c $< -lSDL2 -g

Compteur.o: Compteur.cpp Compteur.hpp
	 	g++ -c $< -lSDL2 -g



clean:
		rm -f *.o *~ $(PROGS)
