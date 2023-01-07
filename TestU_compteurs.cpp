// #include "Graphique.hpp"
// #include "JeuExpt.hpp"
#include <SDL2/SDL.h>
// #include <random>
// #include <stdio.h>
#include <iostream>
#include <ctime>
#include "Compteur.hpp"
#include <chrono>

using namespace std;

int main()
{
//==================================INI=========================================
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        throw runtime_error("Impossible d'initialiser la SDL");
    }
    SDL_Window* window = SDL_CreateWindow("Titre de la fenetre", SDL_WINDOWPOS_UNDEFINED, 0, 800 , 1000, SDL_WINDOW_SHOWN);
    if( window == NULL )
    {
        SDL_Quit(); // penser a fermer SDL
        throw runtime_error("Impossible d'allouer une fenetre");
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL)
    {
        SDL_DestroyWindow(window); // penser a liberer window
        SDL_Quit();                // penser a fermer SDL
        throw runtime_error("Impossible d'allouer un renderer");
    }
    //==============================================================================
    //=================================LEFT=========================================
    Chiffre ZERO(renderer, 30, 100, 100, 0);
    Chiffre UN(renderer, 30, 100, 100, 1);
    Chiffre DEUX(renderer, 30, 100, 100, 2);
    Chiffre TROIS(renderer, 30, 100, 100, 3);
    Chiffre QUATRE(renderer, 30, 100, 100, 4);
    Chiffre CINQ(renderer, 30, 100, 100, 5);
    Chiffre SIX(renderer, 30, 100, 100, 6);
    Chiffre SEPT(renderer, 30, 100, 100, 7);
    Chiffre HUIT(renderer, 30, 100, 100, 8);
    Chiffre NEUF(renderer, 30, 100, 100, 9);

    std::vector<Chiffre> CHIFFRES = {ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF};
    //==============================================================================
    //===================================RIGHT======================================
    Nombre NBR(renderer, 10, 10, 200, 0);
    //==============================================================================

    SDL_Event event;
    bool run = true;
    bool left, right = false;
    while(run)
    {
        SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
        SDL_RenderClear( renderer );

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : run = false; break;
                case SDL_KEYDOWN :
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        right = true;
                        left = false;
                    }
                    if(event.key.keysym.sym == SDLK_LEFT)
                    {
                        right = false;
                        left = true;
                    }
                    break;
            }
        }

        if(left)
        {
            for(auto N : CHIFFRES)
            {
                while(SDL_PollEvent(&event))
                {
                    switch(event.type)
                    {
                        case SDL_QUIT : run = false; break;
                        case SDL_KEYDOWN :
                            if(event.key.keysym.sym == SDLK_RIGHT)
                            {
                                right = true;
                                left = false;
                            }break;
                    }
                }
                if(!run || !left)
                    break;

                N.affiche();
                SDL_RenderPresent(renderer);

                SDL_Delay(500);
                SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
                SDL_RenderClear( renderer );
            }
        }

        if(right)
        {
            NBR.affiche();
            ++NBR;
            SDL_Delay(200);
        }
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
