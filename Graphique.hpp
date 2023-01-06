#ifndef GRAPH
#define GRAPH

#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "Oiseau.h"
#include "Environnement.hpp"
#include "Compteur.hpp"
#include "Image.hpp"

using namespace std;

class Graphique
{
private:
    //purement graphique
    SDL_Window* window;
    SDL_Renderer* renderer;

    int Largeur;
    int Hauteur;

    //evenements
    int touche_appuyee;
    bool quitter;
    SDL_Event event;
    bool reset;
    int Etat = 0;// trois etats possibles : 'DEBUT' : 0, 'JEU' : 1 , 'PAUSE' , 2 et 'MORT' : 3
    Nombre compteur;
    Image imgFin;

public:
    Graphique(int largeur, int hauteur);

    void ecouter();

    bool get_quitter(void) const{return quitter;}
    bool get_touche_enfoncee(void)
    {
        if(touche_appuyee == 1)
        {
            touche_appuyee=2;
            return true;
        }
        return false;
    }
    bool get_reset()const
    {
        return reset;
    }
    int get_Etat()const
    {
        return Etat;
    }
    SDL_Renderer* get_renderer()const
    {
        return renderer;
    }
    Nombre& get_compteur()// on utilisera ++ get_compteur
    {
        return compteur;
    }

    void set_reset(bool rst)
    {
        reset = rst;
    }
    void set_Etat(int etat)
    {
        Etat = etat;
    }

    ~Graphique()
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void affiche_fond()const  //le const ne fait pas d'erreur car on modifie la valeur du pointeur
    {
        SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
        SDL_RenderClear( renderer );
    }

    void affiche_oiseau(Oiseau B)const;

    template<class RNG>
    void affiche_obstacle(Environnement<RNG> Env)const;

    void affiche_pause()const;

    void affiche_fin()const
    {
        if(Etat == 3)
            imgFin.affiche_image();
    }

    template<class RNG>
    void affiche_tout(Environnement<RNG> Env)const
    {
        affiche_fond();
        affiche_oiseau(Env.get_oiseau());
        affiche_obstacle<RNG>(Env);
        affiche_pause();
        compteur.affiche();
        affiche_fin();

        SDL_RenderPresent(renderer);
    }
};

//===============================================================================================================================//

template<class RNG>
void Graphique::affiche_obstacle(Environnement<RNG> Env)const
{
    Obstacle Obs_g = Env.get_obstacle_gauche();
    Obstacle Obs_d = Env.get_obstacle_droite();
    SDL_Rect rectangle_1;
    SDL_Rect rectangle_2;
    SDL_Rect rectangle_3;
    SDL_Rect rectangle_4;

    SDL_SetRenderDrawColor(renderer, 2, 215, 102, 255);

    rectangle_1.x = Obs_g.get_pos_hor() - 0.5 * Obs_g.get_large();
    rectangle_1.y = 0;
    rectangle_1.w =  Obs_g.get_large();
    rectangle_1.h = Obs_g.get_bas();
    SDL_Rect Robert_1(rectangle_1);
    SDL_RenderFillRect(renderer, &Robert_1);

    rectangle_2.x = Obs_g.get_pos_hor() - 0.5 * Obs_g.get_large();
    rectangle_2.y = Obs_g.get_haut();
    rectangle_2.w =  Obs_g.get_large();
    rectangle_2.h = Env.get_taille_vert() - Obs_g.get_haut();
    SDL_Rect Robert_2(rectangle_2);
    SDL_RenderFillRect(renderer, &Robert_2);


    rectangle_3.x = Obs_d.get_pos_hor() - 0.5 * Obs_d.get_large();
    rectangle_3.y = 0;
    rectangle_3.w =  Obs_d.get_large();
    rectangle_3.h = Obs_d.get_bas();
    SDL_Rect Robert_3(rectangle_3);
    SDL_SetRenderDrawColor(renderer, 2, 215, 102, 255);
    SDL_RenderFillRect(renderer, &Robert_3);

    rectangle_4.x = Obs_d.get_pos_hor() - 0.5 * Obs_d.get_large();
    rectangle_4.y = Obs_d.get_haut();
    rectangle_4.w =  Obs_d.get_large();
    rectangle_4.h = Env.get_taille_vert() - Obs_d.get_haut();
    SDL_Rect Robert_4(rectangle_4);
    SDL_RenderFillRect(renderer, &Robert_4);
}
#endif
