PROGS=main TestU_compteurs TestU_image TestU_contact

all: $(PROGS)

main: main.o Graphique.o Compteur.o
		g++ -o $@ $^ -lSDL2 -g

TestU_compteurs: TestU_compteurs.o Compteur.o
		g++ -o $@ $^ -lSDL2 -g

TestU_image: TestU_image.o
		g++ -o $@ $^ -lSDL2 -g

TestU_contact: TestU_contact.o Graphique.o Compteur.o
		g++ -o $@ $^ -lSDL2 -g

main.o: main.cpp Jeu.hpp Environnement.hpp Oiseau.h Obstacle.h Graphique.hpp
		g++ -c $< -lSDL2 -g

TestU_compteurs.o: TestU_compteurs.cpp Compteur.hpp
		g++ -c $< -lSDL2 -g

TestU_image.o: TestU_image.cpp Image.hpp
		g++ -c $< -lSDL2 -g

Graphique.o: Graphique.cpp Graphique.hpp Image.hpp Environnement.hpp Oiseau.h Obstacle.h
		g++ -c $< -lSDL2 -g

Compteur.o: Compteur.cpp Compteur.hpp
	 	g++ -c $< -lSDL2 -g

TestU_contact.o: TestU_contact.cpp Jeu.hpp Environnement.hpp Oiseau.h Obstacle.h Graphique.hpp
		g++ -c $< -lSDL2 -g


clean:
		rm -f *.o *~ $(PROGS)
