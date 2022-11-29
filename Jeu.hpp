#ifndef JEU
#define JEU
#include "Environnement.hpp"
#include "Graphique.hpp"
#include <SDL2/SDL.h>
#include <random>

template<class RNG>
class Jeu
{
  private:
    Environnement<RNG> Env;
  public:
    Jeu(RNG G): Env(G){}
    void run();
};

template<class RNG>
void Jeu<RNG>::run()
{
  Graphique A(Env.get_taille_hor(),Env.get_taille_vert());
  bool run=true;
  while(run)
  {
    A.affiche_tout<RNG>(Env);
    A.ecouter();
    if(A.get_quitter())
    {
      run=false;
    }
    Env.tombe_oiseau();
    Env.avance_tuyaux();
    Env.change_obstacle_si_necessaire();

    if(A.get_touche_enfoncee())
    {
      Env.saute_oiseau();
    }
    SDL_Delay(10);
  }
}
#endif
