#include "Environement.hpp"
#define G  6,6742e-11;
using namespace std;

bool Environement::touche_ou_pas()
{
  if(bird.get_poste_fixe() + bird.get_rayon() < obstacle_arriere.get_poste_fixe() - obstacle_arriere.get_large() ||
     bird.get_poste_fixe() - bird.get_rayon() > obstacle_arriere.get_poste_fixe() + obstacle_arriere.get_large() && bird.get_poste_fixe() + bird.get_rayon() < obstacle_avant.get_poste_fixe() - obstacle_avant.get_large() ||
     bird.get_poste_fixe() - bird.get_rayon() > obstacle_avant.get_poste_fixe())
    return(false);
  else if( (bird.get_pos() - bird.get_rayon() > obstacle_arriere.get_bas() && bird.get_pos() + bird.get_rayon() < obstacle_arriere.get_haut()) ||
           (bird.get_pos() - bird.get_rayon() > obstacle_arriere.get_bas() && bird.get_pos() + bird.get_rayon() < obstacle_arriere.get_haut())
    return(false);
  else
    return(true);
}

void Environement::change_obstacle_si_necessaire()
{
  if( obstacle_arriere.get_pos() + obstacle_arriere.get_large() <= 0 ) // coordonées de la fenetre (0,0) en bas a gauche !
  {
    obstacle_arriere = obstacle_avant;
    obstacle_avant = Obstacle(aleas, taille_fenetre_horizontale, taille_fenetre_verticale, bird.get_rayon());
  }
}

void Environnement::avance_oiseau()
{
  double poid = bird.get_masse()*G;
  // double Force_ini = 543;
  double a = (poid + Force_ini)/bird.get_masse();
  bird.set_vit(bird.get_vit() + dt * a);
  bird.set_pos(bird.get_pos() + dt * bird.get_vit() + dt * dt/2 * a)
}

void Environnement::avance_tuyaux()
{
  obstacle_avant.set_pos(obstacle_avant.get_pos() + dt*vitesse_orizontale + vitesse_orizontale) // /!\ valable que si la vitessse est constante !!
}
