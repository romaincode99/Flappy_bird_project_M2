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
    RNG G_perso;
public:
    Jeu(RNG& G): Env(G), G_perso(G){}
    Jeu(RNG& G, Environnement<RNG> env): Env(env), G_perso(G){}
    void run();
};

template<class RNG>
void Jeu<RNG>::run()
{
    Graphique A(Env.get_taille_hor(),Env.get_taille_vert());

    bool ChangeScore = true; //indique si le score peut Ã©voluer!
    bool run = true;
    while(run)
    {
        if(A.get_reset())
        {
            A.set_Etat(0);
            Environnement<RNG> EnvRst(G_perso);
            Env = EnvRst;
            A.get_compteur().set_zero();
            ChangeScore = true;

            A.set_reset(false);
        }

        A.affiche_tout<RNG>(Env);
        A.ecouter();

        if(A.get_quitter())
        {
            run=false;
        }
        try
        {
            Env.touche_pas();
            if(A.get_Etat() == 1) // 1 <=> JEU
            {
                Env.tombe_oiseau();
                Env.avance_tuyaux();
                if(Env.EstPasse() && ChangeScore)
                {
                    ++A.get_compteur();
                    ChangeScore = false;
                }
                if(Env.change_obstacle_si_necessaire())
                {
                    ChangeScore = true;
                }
            }
        }
        catch( logic_error msg )
        {
            A.set_Etat(3); // 3 <==> MORT
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
