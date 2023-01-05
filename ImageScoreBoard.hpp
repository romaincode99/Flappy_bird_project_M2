#ifndef IMG
#define IMG

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

class ImageScoreBoard
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture* image;

        int taille_x;
        int taille_y;

    public:
        ImageScoreBoard(SDL_Renderer* rd, const char* chemin):renderer(rd), image(nullptr), taille_x(0), taille_y(0)
        {
            SDL_Surface* monImage = SDL_LoadBMP(chemin);
            image = SDL_CreateTextureFromSurface(renderer,image);  //La texture monImage contient maintenant l'image importée
            if(!image)
            {
                printf("Erreur de chargement de l'image : %s",SDL_GetError());
                return -1;
            }
            SDL_FreeSurface(image);
            SDL_Rect src{0, 0, 0, 0};
            SDL_Rect dst{ 0, 0, taille_x, taille_y};
            SDL_QueryTexture(image, nullptr, nullptr, &src.w, &src.h);
        } // /!\ SDL ne supporte les image que en format bitmap !

        ImageScoreBoard(SDL_Renderer* rd, const char* chemin, int x, int y):renderer(rd), image(nullptr), taille_x(x), taille_y(y)
        {
            SDL_Surface* monImage = SDL_LoadBMP(chemin);
            image = SDL_CreateTextureFromSurface(renderer,image);  //La texture monImage contient maintenant l'image importée
            if(!image)
            {
                printf("Erreur de chargement de l'image : %s",SDL_GetError());
                return -1;
            }
            SDL_FreeSurface(image);

            SDL_Rect src{0, 0, 0, 0};
            SDL_Rect dst{ 0, 0, taille_x, taille_y};
            SDL_QueryTexture(image, nullptr, nullptr, &src.w, &src.h);
        } // /!\ SDL ne supporte les image que en format bitmap !

        ImageScoreBoard~
        {
            destroyTexture(image);
        }

        void affiche_image()const
        {
            SDL_RenderCopy(renderer, image, nullptr, nullptr); // Affiche ma texture sur touts l'écran
            SDL_RenderPresent(renderer);
        }

        std::pair<int, int> get_taille()
        {
            return make_pair(taille_x, taille_y);
        }

        void set_taille(int x, int y)
        {
            taille_x = x;
            taille_y = y;
            SDL_Rect src{0, 0, 0, 0};
            SDL_Rect dst{ 0, 0, taille_x, taille_y};
            SDL_QueryTexture(image, nullptr, nullptr, &src.w, &src.h);
        }


};

#endif
