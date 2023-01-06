#include "Graphique.hpp"

Graphique::Graphique(int largeur, int hauteur):quitter(false), touche_appuyee(0), reset(false), Largeur(largeur), Hauteur(hauteur), imgFin("images/imgFin.bmp")
{
    if( SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
        throw runtime_error("Impossible d'initialiser la SDL");
    }
    window=SDL_CreateWindow("Flappy Bird !", SDL_WINDOWPOS_UNDEFINED, 0, largeur , hauteur, SDL_WINDOW_SHOWN);
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

    compteur = Nombre(renderer, 10, 10, 30, 0);
    imgFin.set_renderer(renderer);
    imgFin.set_pos(40, 50);
    imgFin.set_taille(largeur - 80, hauteur - 100);
    imgFin.Activate();

//     const SDL_VideoInfo* resolution = NULL;
//     resolution = SDL_GetVideoInfo();
//     int W = resolution->current_w;
//     int H = resolution->current_h;
//     std::cout<<W<<" eet H : "<<H<<std::endl;
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
                Etat = 1;
            }
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                if(Etat == 1)
                Etat = 2;//2 <==> PAUSE
                else if(Etat == 2)
                Etat = 1;
            }
            if(event.key.keysym.sym == SDLK_r)
                if(Etat == 1)
                    reset = true;
            if(event.key.keysym.sym == 13)//13 correspond à la touche entrer
            {
                if(Etat == 3)
                reset = true;
            }
            break;
            case SDL_KEYUP: if(event.key.keysym.sym == SDLK_SPACE) touche_appuyee = 0; break;
        }
    }
}

void Graphique::affiche_oiseau(Oiseau B)const
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


void Graphique::affiche_pause()const
{
    if(Etat == 2)
    {
        int large_rect = 80;
        int long_rect = 3 * large_rect;

        int s = Largeur;
        int l = Hauteur;
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
}

// void Graphique::affiche_fin()const
// {
//     if(Etat == 3)
//     {
//         SDL_Rect rectangle_fond;
//         int decalageL = 40;
//         int decalageH = 50;
//         rectangle_fond.x = decalageL;
//         rectangle_fond.y = decalageH;
//         rectangle_fond.w = Largeur - 2 * decalageL;
//         rectangle_fond.h = Hauteur - 2 * decalageH;
//
//         SDL_SetRenderDrawColor(renderer, 134, 6, 6, 255);
//         SDL_RenderFillRect(renderer, &rectangle_fond);
//     }
// }
