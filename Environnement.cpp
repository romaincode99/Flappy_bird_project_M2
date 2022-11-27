#include "Environnement.hpp"

//#define G  6.6742e-11;
using namespace std;

template<class RNG>
bool Environnement<RNG>::touche_ou_pas(void) {
    if (bird.get_pos_hor() + bird.get_rayon() < obstacle_arriere.get_pos_hor() - obstacle_arriere.get_large() ||
        bird.get_pos_hor() - bird.get_rayon() > obstacle_arriere.get_pos_hor() + obstacle_arriere.get_large() &&
        bird.get_pos_hor() + bird.get_rayon() < obstacle_avant.get_pos_hor() - obstacle_avant.get_large() ||
        bird.get_pos_hor() - bird.get_rayon() > obstacle_avant.get_pos_hor())
        return (false);
    else if ((bird.get_pos() - bird.get_rayon() > obstacle_arriere.get_bas() &&
              bird.get_pos() + bird.get_rayon() < obstacle_arriere.get_haut()) ||
             (bird.get_pos() - bird.get_rayon() > obstacle_arriere.get_bas() &&
              bird.get_pos() + bird.get_rayon() < obstacle_arriere.get_haut()))
        return (false);
    else if (bird.get_pos() < 0 || bird.get_pos() > taille_fenetre_verticale)
        return (false);
    else
        return (true);
}

template<class RNG>
void Environnement<RNG>::change_obstacle_si_necessaire() {
    if (obstacle_arriere.get_pos_hor() + obstacle_arriere.get_large() <=
        0) // coordonées de la fenetre (0,0) en bas a gauche !
    {
        obstacle_arriere = obstacle_avant;
        obstacle_avant = Obstacle(aleas, taille_fenetre_horizontale, taille_fenetre_verticale, bird.get_rayon());
    }
}

template<class RNG>
void Environnement<RNG>::avance_oiseau() {
    cout<<"casse les couilles"<<endl;
    double poids = bird.get_masse() * Gr;
    double a = (poids) / bird.get_masse();
    bird.set_vit(bird.get_vit() + dt * a);
    bird.set_pos(bird.get_pos() + dt * bird.get_vit() + dt * dt / 2 * a);
}

template<class RNG>
void Environnement<RNG>::avance_tuyaux() {
//TODO A Finir !!
    obstacle_avant.set_pos_hor(obstacle_avant.get_pos_hor() + dt * vitesse_horizontale); // /!\ valable que si la vitessse est constante !!
}
