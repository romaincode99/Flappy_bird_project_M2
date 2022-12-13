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
    int compteur = 0;
    RNG G_perso;
  public:
    Jeu(RNG& G): Env(G), G_perso(G){}
    void run();
};

template<class RNG>
void Jeu<RNG>::run()
{
  Graphique A(Env.get_taille_hor(),Env.get_taille_vert());
  bool run = true;
  while(run)
  {
    if(A.get_reset())
    {
      std::cout<<A.get_reset()<<std::endl;
      Environnement<RNG> EnvRst(G_perso);
      Env = EnvRst;

      compteur = 0;

      A.set_echap(true);
      A.set_reset(false);
    }

    A.affiche_tout<RNG>(Env, A.get_echap());
    A.ecouter();

    if(A.get_quitter())
    {
      run=false;
    }
    try
    {
      if(Env.touche_pas() && !A.get_echap())
      {
        Env.tombe_oiseau();
        Env.avance_tuyaux();
        if(Env.change_obstacle_si_necessaire())
       {
         compteur += 1;
         std::cout<<"score : "<<compteur<<std::endl;
       }
      }
    }
    catch( logic_error msg )
    {
      std::cout<<msg.what()<<"!\n";
    }

    if(A.get_touche_enfoncee())
    {
      Env.saute_oiseau();
    }
    SDL_Delay(10);
  }
}
#endif
