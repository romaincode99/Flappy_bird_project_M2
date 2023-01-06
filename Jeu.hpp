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
    Jeu(RNG& G, Environnement<RNG>& env): Env(env), G_perso(G){}
    void run();
};

template<class RNG>
void Jeu<RNG>::run()
{
    Graphique Graph(Env.get_taille_hor(),Env.get_taille_vert());

    bool ChangeScore = true; //indique si le score peut évoluer!
    bool run = true;
    while(run)
    {
        Graph.ecouter();
        if(Graph.get_quitter())
        {
            run=false;
        }

        if(Graph.get_reset())
        {
            Graph.set_Etat(0);
            Environnement<RNG> EnvRst(G_perso);
            Env = EnvRst;
            Graph.get_compteur().set_zero();
            ChangeScore = true;

            Graph.set_reset(false);
            Graph.affiche_tout<RNG>(Env);
        }

        try
        {
            Env.touche_pas();//renvvoie une exeption si on touche !
            if(Graph.get_Etat() == 1) // 1 <=> JEU
            {
                Env.tombe_oiseau();
                Env.avance_tuyaux();
                if(Env.EstPasse() && ChangeScore)
                {
                    ++Graph.get_compteur();
                    ChangeScore = false;
                }
                if(Env.change_obstacle_si_necessaire())
                {
                    ChangeScore = true;
                }
                if(Graph.get_touche_enfoncee())
                {
                    Env.saute_oiseau();
                }
            }
        }
        catch( logic_error msg )
        {
            if(Graph.get_Etat() != 3)
            {
                Graph.set_Etat(3); // 3 <==> MORT
            }
            // std::cout<<msg.what()<<"!\n";
        }
        Graph.affiche_tout<RNG>(Env);
        SDL_Delay(10);
    }
}
#endif
