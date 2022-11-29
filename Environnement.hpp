#ifndef ENV
#define ENV

#include "Oiseau.h"
#include "Obstacle.h"
#include <vector>
#include <cmath>

const double pi = std::acos(-1);

using namespace std;

template<class RNG>
class Environnement {
public:
    double vitesse_horizontale;

    Obstacle obstacle_gauche;
    Obstacle obstacle_droite;

    Oiseau bird;

    int taille_fenetre_horizontale;
    int taille_fenetre_verticale;

    RNG aleas;

    double dt;

    double Gr;

// public:
    Environnement(RNG G, double VH = -250., int T_horiz = 800, int T_vert = 1023,  int taille_oiseau = 40,
                  double dt_ = 1e-2, double Gr_ = 9.81 * 0.5e3) :  vitesse_horizontale(VH),
                                                           obstacle_gauche(G, T_horiz / 2, T_vert, taille_oiseau),
                                                           obstacle_droite(G, T_horiz, T_vert, taille_oiseau),
                                                           dt(dt_),
                                                           bird(T_horiz / 4, 0., 0.02, taille_oiseau),
                                                           taille_fenetre_horizontale(T_horiz),
                                                           taille_fenetre_verticale(T_vert),
                                                           Gr(Gr_), aleas(G) {};
//TODO Pourquoi on se sert de la masse ??

    bool touche_ou_pas(void);

    void change_obstacle_si_necessaire();

    void tombe_oiseau();
    void saute_oiseau();
    void avance_tuyaux();

    int get_taille_hor()const{return taille_fenetre_horizontale;}
    int get_taille_vert()const{return taille_fenetre_verticale;}

    Oiseau get_oiseau(){return bird;}
    Obstacle get_obstacle_gauche(){return obstacle_gauche;}
    Obstacle get_obstacle_droite(){return obstacle_droite;}

};

//=================================================================================================================================================

//fonction touche ou touche pas renvoie true quand touche pas et false si on touche
template<class RNG>
bool Environnement<RNG>::touche_ou_pas(void) //à la fois obstacle et fenetre
{
    if (bird.get_pos_hor() + bird.get_rayon() < obstacle_droite.get_pos_hor() - obstacle_droite.get_large() ||
        bird.get_pos_hor() - bird.get_rayon() > obstacle_droite.get_pos_hor() + obstacle_droite.get_large() &&
        bird.get_pos_hor() + bird.get_rayon() < obstacle_gauche.get_pos_hor() - obstacle_gauche.get_large() ||
        bird.get_pos_hor() - bird.get_rayon() > obstacle_gauche.get_pos_hor())
        return (false);
    else if ((bird.get_pos() - bird.get_rayon() > obstacle_droite.get_bas() &&
              bird.get_pos() + bird.get_rayon() < obstacle_droite.get_haut()) ||
             (bird.get_pos() - bird.get_rayon() > obstacle_droite.get_bas() &&
              bird.get_pos() + bird.get_rayon() < obstacle_droite.get_haut()))
        return (false);
    else if (bird.get_pos() < 0 || bird.get_pos() > taille_fenetre_verticale)
        return (false);
    else
        return (true);
}

template<class RNG>
void Environnement<RNG>::change_obstacle_si_necessaire() {
    if (obstacle_gauche.get_pos_hor() + obstacle_gauche.get_large() <= 0) // coordonnées de la fenetre (0,0) en bas a gauche !
    {
        obstacle_gauche = obstacle_droite;
        obstacle_droite = Obstacle(aleas, taille_fenetre_horizontale, taille_fenetre_verticale, bird.get_rayon());
    }
}

template<class RNG>
void Environnement<RNG>::tombe_oiseau()
{
    double a = 60 + Gr;
    bird.set_vit(bird.get_vit() + dt * a);
    bird.set_pos(bird.get_pos() + dt * bird.get_vit() + dt * dt / 2 * a);
    // std::cout <<bird.get_pos() + dt * bird.get_vit() + dt * dt / 2 * a << '\n';
    // cout<<bird.get_pos()<<endl;
}

template<class RNG>
void Environnement<RNG>::saute_oiseau()
{
  bird.set_vit(0 * bird.get_vit()-1300);
}

template<class RNG>
void Environnement<RNG>::avance_tuyaux()
{
    obstacle_gauche.set_pos_hor(obstacle_gauche.get_pos_hor() + dt * vitesse_horizontale); // /!\ valable que si la vitesse est constante !!
    obstacle_droite.set_pos_hor(obstacle_droite.get_pos_hor() + dt * vitesse_horizontale);
}

#endif

//METRE UNE FIN À FLAPPY BIRD À 10 000