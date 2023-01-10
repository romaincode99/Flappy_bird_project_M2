#ifndef PROJET_FLAPPY_BIRD_OBSTACLE_H
#define PROJET_FLAPPY_BIRD_OBSTACLE_H

#include <random>
#include <iostream>

using namespace std;

class Obstacle {
private:
    int bas; //c'est le bas du tuyau du haut
    int haut; //c'est le haut du tuyau du bas
    double pos_hor;
    int largeur = 70;

public:
    template<class RNG>
    Obstacle(RNG&   G, int hor, int taille_fenetre_vert, int taille_oiseau);

    double get_bas()const {
        return bas;
    }

    double get_haut()const {
        return haut;
    }

    double get_large()const {
        return largeur;
    }

    double get_pos_hor()const {
        return pos_hor;
    }

    void set_pos_hor(double pos) {
        pos_hor = pos;
    }
};

template<class RNG>
Obstacle::Obstacle(RNG& G, int taille_fenetre_hor, int taille_fenetre, int taille_oiseau)
{
    int taille_trou = 11 * taille_oiseau;
    normal_distribution<double> N1(taille_fenetre / 3. - taille_oiseau, 300);
    normal_distribution<double> N2(2 * taille_fenetre / 3. - taille_oiseau, 300);
    bernoulli_distribution Bernou(0.5);

    int b = 0;
    if(Bernou(G))
      b = N1(G);
    else
      b = N2(G);

    b = min(int(b), taille_fenetre - taille_trou - taille_oiseau);
    b = max(int(b), taille_oiseau); // taille oiseau ici a la meme taille que le petit bout du tuyau !

    bas = b;
    haut = bas + taille_trou;
    pos_hor = taille_fenetre_hor + largeur / 2;
}

#endif //PROJET_FLAPPY_BIRD_OBSTACLE_H
