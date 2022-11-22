//
// Created by justi on 11/11/2022.
//

#ifndef PROJET_FLAPPY_BIRD_OBSTACLE_H
#define PROJET_FLAPPY_BIRD_OBSTACLE_H

#include <random>
#include <iostream>

using namespace std;

class Obstacle {
private:
    int bas; //Mettre des int
    int haut;
    int pos_hor;
    int largeur = 10;// a determiner
public:
    template<class RNG>
    Obstacle(RNG G, int hor, int taille_fenetre_vert, int ray);

    double get_bas() {
        return bas;
    }

    double get_haut() {
        return haut;
    }

    double get_large() {
        return largeur;
    }

    double get_pos_hor() {
        return pos_hor;
    }

    void set_pos_hor(double pos) {
        pos_hor = pos;
    }
};

template<class RNG>
Obstacle::Obstacle(RNG G, int hor, int taille_fenetre_vert, int ray) {
    int taille_fenetre = taille_fenetre_vert;
    int taille_oiseau = ray;
    normal_distribution<double> N1(taille_fenetre / 3. + taille_oiseau, 1);
    normal_distribution<double> N2(2 * taille_fenetre / 3. + taille_oiseau, 1);
    int h = 1 / 2 * N1(G) + 1 / 2 * N2(G);
    h = min(h, 2 * taille_oiseau);
    h = max(h, taille_fenetre);
    normal_distribution<double> U(2 * taille_oiseau, 1);
    int d = min(U(G), 1.5 * taille_oiseau);
    d = max(d, h);
    haut = h;
    bas = haut - d;
    pos_hor = hor + largeur / 2;
}

#endif //PROJET_FLAPPY_BIRD_OBSTACLE_H
