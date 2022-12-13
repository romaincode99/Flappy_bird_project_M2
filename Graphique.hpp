#ifndef GRAPH
#define GRAPH

#include <SDL2/SDL.h>
#include <iostream>
#include "Oiseau.h"
#include "Environnement.hpp"

using namespace std;

class Graphique
{
  private:
    //purement graphique
    SDL_Window *window;
    SDL_Renderer *renderer;

    //evenements
    int touche_appuyee;
    bool quitter;
    SDL_Event event;
    bool reset;
    bool echap;

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
    bool get_reset()
    {
      return reset;
    }
    bool get_echap()
    {
      return echap;
    }

    void set_reset(bool rst)
    {
      reset = rst;
    }
    void set_echap(bool esp)
    {
      echap = esp;
    }

    ~Graphique()
    {
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
    }

    void affiche_fond()
    {
      SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
      SDL_RenderClear( renderer );
    }

    void affiche_oiseau(Oiseau B);

    template<class RNG>
    void affiche_obstacle(Environnement<RNG> Env);

    template<class RNG>
    void affiche_pause(Environnement<RNG>)const;

    template<class RNG>
    void affiche_tout(Environnement<RNG> Justi, bool pause) // bah c'est justine l'environnement !
    {
      affiche_fond();
      affiche_oiseau(Justi.get_oiseau());
      affiche_obstacle<RNG>(Justi);
      if(pause)
        affiche_pause<RNG>(Justi);

      SDL_RenderPresent(renderer);
    }
};


//===============================================================================================================================//


Graphique::Graphique(int largeur, int hauteur):quitter(false), touche_appuyee(0), reset(false), echap(false)
{
  if( SDL_Init(SDL_INIT_VIDEO) < 0 )
  {
    throw runtime_error("Impossible d'initialiser la SDL");
  }
  window=SDL_CreateWindow("Titre de la fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, largeur , hauteur, SDL_WINDOW_SHOWN);
  if( window == NULL )
  {
      SDL_Quit(); // penser a fermer SDL
      throw runtime_error("Impossible d'allouer une fenetre");
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  if(renderer == NULL)
  {
     SDL_DestroyWindow(window); // penser a liberer window
     SDL_Quit();                // penser a fermer SDL
     throw runtime_error("Impossible d'allouer un renderer");
  }
}

void Graphique::ecouter()
{
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT: quitter=true; break;
      case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_SPACE && touche_appuyee != 2)
        {
          touche_appuyee += 1;
          if(echap)
            echap = !echap;
        }
        if(event.key.keysym.sym == SDLK_ESCAPE)
          echap = !echap;
        if(event.key.keysym.sym == SDLK_r)
          reset = true;
        break;
      case SDL_KEYUP: if(event.key.keysym.sym == SDLK_SPACE) touche_appuyee = 0; break;
    }
  }
}

void Graphique::affiche_oiseau(Oiseau B)
{
  SDL_Rect Robert;
  Robert.x = B.get_pos_hor() - B.get_rayon();
  Robert.y = B.get_pos() - B.get_rayon();
  Robert.w =  B.get_rayon() * 2;
  Robert.h = B.get_rayon() * 2;

  SDL_SetRenderDrawColor(renderer, 201, 215, 102, 255);


  SDL_RenderFillRect(renderer, &Robert);
  SDL_SetRenderDrawColor(renderer, 255, 1, 1, 255);
  SDL_Rect pix;
  pix.x = B.get_pos_hor() - 3;
  pix.y = B.get_pos() - 3;
  pix.w =  6;
  pix.h = 6;
  SDL_RenderFillRect(renderer, &pix);
}

template<class RNG>
void Graphique::affiche_obstacle(Environnement<RNG> Env)
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

template<class RNG>
void Graphique::affiche_pause(Environnement<RNG> Env)const
{
  int large_rect = 80;
  int long_rect = 3 * large_rect;

  int s = Env.get_taille_hor();
  int l = Env.get_taille_vert();
  SDL_Rect rectangle_1;
  SDL_Rect rectangle_2;
  SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);

  rectangle_1.x = 7 * s / 12 - large_rect / 2;
  rectangle_1.y = l / 2 - long_rect / 2;
  rectangle_1.w = large_rect;
  rectangle_1.h = long_rect;

  rectangle_2.x = 5 * s / 12 - large_rect / 2;
  rectangle_2.y = l / 2 - long_rect / 2;
  rectangle_2.w = large_rect;
  rectangle_2.h = long_rect;

  SDL_RenderFillRect(renderer, &rectangle_1);
  SDL_RenderFillRect(renderer, &rectangle_2);
}
#endif
