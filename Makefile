PROGS: main

all: $(PROGS)

main: main.o
		g++ -o $@ $^ -lSDL2 -g

main.o: main.cpp Graphique.hpp Jeu.hpp
		g++ -c $< -lSDL2 -g

clean:
		-rm -f *.o *~ $ (PROGS)
