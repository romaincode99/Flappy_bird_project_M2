#ifndef IMG
#define IMG

#include <iostream>
#include <SDL2/SDL.h>

class Image
{
    private:
        SDL_Renderer* renderer;
        SDL_Texture* image;

        const char* chemin;

        int taille_x;
        int taille_y;

        int pos_x;
        int pos_y;

        SDL_Rect Rendu;

    public:
        Image(SDL_Renderer* rd, const char* chemin):renderer(rd), chemin(chemin), image(nullptr),taille_x(0), taille_y(0), pos_x(0), pos_y(0), Rendu() {}
        // /!\ SDL ne supporte les image que en format bitmap !

        Image(const char* chemin):renderer(nullptr), chemin(chemin), image(nullptr),taille_x(0), taille_y(0), pos_x(0), pos_y(0), Rendu() {}
        // /!\ SDL ne supporte les image que en format bitmap !

        Image(SDL_Renderer* rd, const char* chemin, int taille_x, int taille_y, int pos_x = 0, int pos_y = 0):renderer(rd), chemin(chemin), image(nullptr), taille_x(taille_x), taille_y(taille_y), pos_x(pos_x), pos_y(pos_y), Rendu()
        {
            Rendu.x = pos_x;
            Rendu.y = pos_y;
            Rendu.w = taille_x;
            Rendu.h = taille_y;
        }
        // /!\ SDL ne supporte les image que en format bitmap !

        void Activate()
        {
            SDL_Surface* monImage = SDL_LoadBMP(chemin);
            if(!monImage)
            {
                printf("Erreur lors du chargement de l'image: %s \n", SDL_GetError());
            }
            if(taille_x == 0 && taille_y == 0)
            {
                taille_x = monImage -> w;
                taille_y = monImage -> h;
            }
            image = SDL_CreateTextureFromSurface(renderer,monImage);  //La texture monImage contient maintenant l'image importée
            if(!image)
            {
                printf("Erreur : %s \n",SDL_GetError());//generalement erreur quand on oublie d'initialiser le renderer !
            }
            SDL_FreeSurface(monImage);
        }

        ~Image()
        {
            SDL_DestroyTexture(image);
        }

        std::pair<int, int> get_taille()const
        {
            return std::make_pair(taille_x, taille_y);
        }

        std::pair<int, int> get_pos()const
        {
            return std::make_pair(pos_x, pos_y);
        }

        void set_taille(int x, int y)
        {
            taille_x = x;
            taille_y = y;

            Rendu.w = taille_x;
            Rendu.h = taille_y;
        }

        void set_pos(int x, int y)
        {
            pos_x = x;
            pos_y = y;

            Rendu.x = pos_x;
            Rendu.y = pos_y;
        }

        void set_renderer(SDL_Renderer* rd)
        {
            renderer = rd;
        }

        void affiche_image()const
        {
            SDL_RenderCopy(renderer, image, nullptr, &Rendu); // Affiche ma texture sur tout l'écran
            SDL_RenderPresent(renderer);
        }


};

#endif
