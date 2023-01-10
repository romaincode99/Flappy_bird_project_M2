#ifndef ENV
#define ENV

#include "Oiseau.h"
#include "Obstacle.h"
#include <vector>
#include <cmath>

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

    Environnement(RNG& G, double VH = -250., int T_horiz = 800, int T_vert = 925,  int taille_oiseau = 20, double dt_ = 1e-2, double Gr_ = 9.81 * 0.5e3):vitesse_horizontale(VH),
                                                                                                                                                          obstacle_gauche(G, T_horiz / 2, T_vert, taille_oiseau),
                                                                                                                                                          obstacle_droite(G, T_horiz, T_vert, taille_oiseau),
                                                                                                                                                          dt(dt_),
                                                                                                                                                          bird(T_horiz / 4, 0., taille_oiseau),
                                                                                                                                                          taille_fenetre_horizontale(T_horiz),
                                                                                                                                                          taille_fenetre_verticale(T_vert),
                                                                                                                                                          Gr(Gr_), aleas(G) {};

    bool touche_pas(void)const;
    bool EstPasse()const;

    bool change_obstacle_si_necessaire();

    void tombe_oiseau();
    void saute_oiseau();
    void avance_tuyaux();

    int get_taille_hor()const{return taille_fenetre_horizontale;}
    int get_taille_vert()const{return taille_fenetre_verticale;}

    Oiseau& get_oiseau(){return bird;}
    Obstacle& get_obstacle_gauche(){return obstacle_gauche;}
    Obstacle& get_obstacle_droite(){return obstacle_droite;}

};

//=================================================================================================================================================

template<class RNG>
bool Environnement<RNG>::touche_pas(void)const
{
    if ((bird.get_pos_hor() + bird.get_rayon() > obstacle_gauche.get_pos_hor() - obstacle_gauche.get_large() / 2 &&
         bird.get_pos_hor() - bird.get_rayon() < obstacle_gauche.get_pos_hor() + obstacle_gauche.get_large() / 2) &&
        (bird.get_pos() - bird.get_rayon() < obstacle_gauche.get_bas() ||
         bird.get_pos() + bird.get_rayon() > obstacle_gauche.get_haut())
            )
    {
        throw logic_error("Tu est Mort ... RIP");
        return (false);
    }
    else if(bird.get_pos() - bird.get_rayon() < 0 || bird.get_pos() + bird.get_rayon()> taille_fenetre_verticale)
    {
        throw logic_error("Tu est Mort ... RIP");
        return (false);
    }
    else
        return (true);
}

template<class RNG>
bool Environnement<RNG>::EstPasse()const
{
    if(bird.get_pos_hor() + bird.get_rayon() + 5 > obstacle_gauche.get_pos_hor() + obstacle_gauche.get_large() / 2)//on rajoute les 5 pixels pour etre sur qu'on est bien passé
        return true;
    else
        return false;
}

template<class RNG>
bool Environnement<RNG>::change_obstacle_si_necessaire()//return true si rajoute un obstacle et false sinon (pour compter les obstacles passÃ©s)
{
    if (obstacle_gauche.get_pos_hor() + obstacle_gauche.get_large() <= 0) // coordonnÃ©es de la fenetre (0,0) en bas a gauche !
    {
        obstacle_gauche = obstacle_droite;
        obstacle_droite = Obstacle(aleas, taille_fenetre_horizontale, taille_fenetre_verticale, bird.get_rayon());
        return true;
    }
    return false;
}

template<class RNG>
void Environnement<RNG>::tombe_oiseau()
{
    double a = Gr;
    bird.set_vit(bird.get_vit() + dt * a);
    bird.set_pos(bird.get_pos() + dt * bird.get_vit() + dt * dt / 2 * a);
}

template<class RNG>
void Environnement<RNG>::saute_oiseau()
{
    bird.set_vit(-1200);
}

template<class RNG>
void Environnement<RNG>::avance_tuyaux()
{
    obstacle_gauche.set_pos_hor(obstacle_gauche.get_pos_hor() + dt * vitesse_horizontale); // /!\ valable que si la vitesse est constante !!
    obstacle_droite.set_pos_hor(obstacle_droite.get_pos_hor() + dt * vitesse_horizontale);
}

#endif
