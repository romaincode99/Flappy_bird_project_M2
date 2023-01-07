
#include "Graphique.hpp"
#include "Jeu.hpp"
#include <SDL2/SDL.h>
#include <random>
#include <stdio.h>
#include <ctime>

using namespace std;

int main(){
//int main(int argc, char *argv[]) {
    mt19937 G(time(NULL));
    int choix;
    std::cout
            << "1 pour test du haut de la fenetre quand il ne meurt pas \n2 pour test du haut de la fenetre quand il meurt \n3 pour test du bas de la fenetre quand il ne meurt pas \n"
               "4 pour test du bas de la fenetre quand il meurt \n5 pour test de l'obstacle du bas quand il ne meurt pas \n6 pour test de l'obstacle du bas quand il meurt \n"
               "7 pour test de l'obstacle du haut quand il ne meurt pas \n8 pour test de l'obstacle du haut quand il meurt\n9 pour test du milieu bas des obstacles quand il ne meurt pas \n"
               "10 pour test du milieu bas des obstacles quand il meurt \n11 pour test du milieu haut des obstacles quand il ne meurt pas \n12 pour test du milieu haut des obstacles quand il meurt"
            << endl;
    std::cin >> choix;
    Environnement<mt19937> E(G);

    if (choix == 1) {
        //test haut de la fenetre quand il ne meurt pas
        E.get_oiseau().set_pos(E.get_oiseau().get_rayon());
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 2) {
        //test haut de la fenetre quand il meurt
        E.get_oiseau().set_pos(E.get_oiseau().get_rayon() - 1);
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 3) {
        //test bas de la fenetre quand il ne meurt pas
        E.get_oiseau().set_pos(E.get_taille_vert() - E.get_oiseau().get_rayon());
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 4) {
        //test bas de la fenetre quand il meurt
        E.get_oiseau().set_pos(E.get_taille_vert());
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 5) {
        //test gauche haut de l'obstacle quand il ne meurt pas
        E.get_obstacle_gauche().set_pos_hor(
                E.get_oiseau().get_pos_hor() + E.get_oiseau().get_rayon() + E.get_obstacle_gauche().get_large() / 2);
        E.get_oiseau().set_pos(E.get_obstacle_gauche().get_bas() / 2);
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 6) {
        //test gauche haut de l'obstacle quand il meurt
        E.get_obstacle_gauche().set_pos_hor(
                E.get_oiseau().get_pos_hor() + E.get_oiseau().get_rayon() + E.get_obstacle_gauche().get_large() / 2 -
                1);
        E.get_oiseau().set_pos(E.get_obstacle_gauche().get_bas() / 2);
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 7) {
        //test gauche bas de l'obstacle quand il ne meurt pas
        E.get_obstacle_gauche().set_pos_hor(
                E.get_oiseau().get_pos_hor() + E.get_oiseau().get_rayon() + E.get_obstacle_gauche().get_large() / 2);
        E.get_oiseau().set_pos((E.get_taille_vert() + E.get_obstacle_gauche().get_haut()) / 2);
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 8) {
        //test gauche bas de l'obstacle quand il meurt
        E.get_obstacle_gauche().set_pos_hor(
                E.get_oiseau().get_pos_hor() + E.get_oiseau().get_rayon() + E.get_obstacle_gauche().get_large() / 2 -
                1);
        E.get_oiseau().set_pos((E.get_taille_vert() + E.get_obstacle_gauche().get_haut()) / 2);
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 9) {
        //test bas de l'obstacle quand il ne meurt pas
        E.get_obstacle_gauche().set_pos_hor(E.get_oiseau().get_pos_hor());
        E.get_oiseau().set_pos(E.get_obstacle_gauche().get_bas() + E.get_oiseau().get_rayon());
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 10) {
        //test bas de l'obstacle quand il meurt
        E.get_obstacle_gauche().set_pos_hor(E.get_oiseau().get_pos_hor());
        E.get_oiseau().set_pos(E.get_obstacle_gauche().get_bas() + E.get_oiseau().get_rayon() - 1);
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 11) {
        //test haut de l'obstacle quand il ne meurt pas
        E.get_obstacle_gauche().set_pos_hor(E.get_oiseau().get_pos_hor());
        E.get_oiseau().set_pos(E.get_obstacle_gauche().get_haut() - E.get_oiseau().get_rayon());
        Jeu<mt19937> J(G, E);
        J.run();
    } else if (choix == 12) {
        //test haut de l'obstacle quand il meurt
        E.get_obstacle_gauche().set_pos_hor(E.get_oiseau().get_pos_hor());
        E.get_oiseau().set_pos(E.get_obstacle_gauche().get_haut() - E.get_oiseau().get_rayon() + 1);
        Jeu<mt19937> J(G, E);
        J.run();
    }


    return 0;
}
