#include "Image.hpp"
#include <SDL2/SDL.h>
#include <iostream>
#include <ctime>
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

    Image test("images/imgTEST"); // si on oublile .bnp ou images/ un message d'erreur doit apparaitre !!
    test.set_renderer(renderer);
    test.set_pos(40, 50);
    test.set_taille(800 - 80, 1000 - 100);
    test.Activate();

    SDL_Event event;
    bool run = true;
    while(run)
    {
        SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
        SDL_RenderClear( renderer );

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT : run = false; break;
            }
        }
        // SDL_SetRenderDrawColor( renderer, 14, 241, 250, 255 );
        // SDL_RenderClear( renderer );

        test.affiche_image();

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
