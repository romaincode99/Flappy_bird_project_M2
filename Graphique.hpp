#ifndef GRAPH
#define GRAPH

#include <SDL2/SDL.h>
#include <iostream>

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



    void impulsion_oiseaux();
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
};

#endif
