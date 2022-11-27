#ifndef ENV
#define ENV

#include "Oiseau.h"
#include "Obstacle.h"
#include <vector>


template<class RNG>
class Environnement {
public:
    double vitesse_horizontale;

    Obstacle obstacle_avant;
    Obstacle obstacle_arriere;

    Oiseau bird;

    int taille_fenetre_horizontale;
    int taille_fenetre_verticale;

    RNG aleas;

    double dt;

    double Gr;

// public:
    Environnement(RNG G, double VH = -50., int T_horiz = 800, int T_vert = 1080, int ray_obs = 40,
                  double dt_ = 1. / 60, double Gr_ = 6.6742e-11) : vitesse_horizontale(VH),
                                                                   obstacle_avant(G, T_horiz / 2, T_vert, ray_obs),
                                                                   obstacle_arriere(G, T_horiz, T_vert, ray_obs),
                                                                   dt(dt_),
                                                                   bird(T_horiz / 4, 0., 0.02),
                                                                   taille_fenetre_horizontale(T_horiz),
                                                                   taille_fenetre_verticale(T_vert),
                                                                   Gr(Gr_), aleas(G) {};
//TODO Pourquoi on se sert de la masse ??

    bool touche_ou_pas(void);

    void change_obstacle_si_necessaire();

    void avance_oiseau();

    void avance_tuyaux();
};

#endif

//METRE UNE FIN À FLAPPY BIRD À 10 000
