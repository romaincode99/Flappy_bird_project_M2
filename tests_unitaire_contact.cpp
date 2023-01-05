
#include "Graphique.hpp"
#include "Jeu.hpp"
#include <SDL2/SDL.h>
#include <random>
#include <stdio.h>
#include <ctime>

using namespace std;

int main() {
    mt19937 G(time(NULL));
    int choix;
    std::cout
            << "1 pour test du haut de la fenetre \n 2 pour test du bas de la fenetre quand il ne meurt pas \n 3 pour test du bas de la fenetre quand il meurt"
            << endl;
    std::cin >> choix;
    Environnement<mt19937> E(G);

    if (choix == 1) {
        //test haut de la fenetre
        E.get_oiseau().set_pos(E.get_oiseau().get_rayon());
        Jeu<mt19937> J(G, E);
        J.run();
    }
    else if (choix == 2) {
        //test bas de la fenetre quand il ne meurt pas
        E.get_oiseau().set_pos(E.get_taille_vert() - E.get_oiseau().get_rayon());
        Jeu<mt19937> J(G, E);
        J.run();
    }
    else if (choix == 3) {
        //test bas de la fenetre quand il meurt
        E.get_oiseau().set_pos(E.get_taille_vert());
        Jeu<mt19937> J(G, E);
        J.run();
    }


    return 0;
}
