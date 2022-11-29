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

  public:
    Graphique(int largeur, int hauteur):quitter(false), touche_appuyee(0){
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



    // void impulsion_oiseaux();
    void ecouter()
    {
      while(SDL_PollEvent(&event))
      {
        switch(event.type)
        {
          case SDL_QUIT: quitter=true; break;
          case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_SPACE && touche_appuyee != 2)
              touche_appuyee += 1;
            break;
          case SDL_KEYUP: if(event.key.keysym.sym == SDLK_SPACE) touche_appuyee = 0; break;
        }
      }
    }

    bool get_quitter(void) const{return quitter;}
    bool get_touche_enfoncee(void)
    {
      if(touche_appuyee == 1){
        touche_appuyee=2;
        return true;
      }
      return false;
    }

    ~Graphique(){
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
    }

    void affiche_fond()
    {
      SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
      SDL_RenderClear( renderer );
      //SDL_RenderPresent(renderer);
    }

    void affiche_oiseau(Oiseau B)
    {
      SDL_Rect rectangle;
      rectangle.x = B.get_pos_hor();
      rectangle.y = B.get_pos();
      rectangle.w =  B.get_rayon();
      rectangle.h = B.get_rayon();
      SDL_Rect Robert(rectangle);

      SDL_SetRenderDrawColor(renderer, 201, 215, 102, 255);


      SDL_RenderFillRect(renderer, &Robert);
    }

    template<class RNG>
    void affiche_obstacle(Environnement<RNG> Env)
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
    void affiche_tout(Environnement<RNG> Justi)
    {
      affiche_fond();
      affiche_oiseau(Justi.get_oiseau());
      affiche_obstacle<RNG>(Justi);
      SDL_RenderPresent(renderer);
    }
};

#endif
