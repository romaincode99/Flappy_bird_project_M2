#ifndef ENV
#define ENV

#include "Oiseau.h"
#include "Obstacle.h"
#include <vector>

template<class RNG>
class Environnement {
private:
    double vitesse_orizontale = -50;

    Obstacle obstacle_avant;
    Obstacle obstacle_arriere;

    Oiseau bird;

    int taille_fenetre_horizontale = 600;
    int taille_fenetre_verticale = 700;

    RNG aleas;

    int dt = 1. / 60;// 1/fps

public:
    //Environnement() : aleas(RNG){};
    bool touche_ou_pas();

    void change_obstacle_si_necessaire();

    // ------A FAIRE-------
    void avance_oiseau();

    void avance_tuyaux();
    //-----------------
};

#endif

//METRE UNE FIN À FLAPPY BIRD À 10 000
