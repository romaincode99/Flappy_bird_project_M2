#ifndef COMPTEUR
#define COMPTEUR

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <charconv>
#include <list>

class Chiffre
{
    private:

        SDL_Renderer* renderer;
        int largeur_trait;
        int rapportLongLarg = 6;
        int xpos;
        int ypos;
        int chiffre; //entre 0 et 9 !!
        std::vector<SDL_Rect> barrechiffre;

        int r;
        int v;
        int b;

        void affiche_ch(bool haut, bool haut_gauche, bool haut_droite, bool milieu, bool bas_gauche, bool bas_droite, bool bas)const;
    public:
        Chiffre(SDL_Renderer* rd): renderer(rd), largeur_trait(1), xpos(0), ypos(0), chiffre(0), r(134), v(6), b(6){}
        Chiffre(): renderer(nullptr), largeur_trait(1), xpos(0), ypos(0), chiffre(0), r(134), v(6), b(6){}
        Chiffre(SDL_Renderer* rd, int hauteur): renderer(rd), largeur_trait(1), xpos(0), ypos(0), chiffre(0), r(134), v(6), b(6){largeur_trait = hauteur / (rapportLongLarg + 2);}
        Chiffre(SDL_Renderer * rend, int LT, int x, int y, int ch): renderer(rend), largeur_trait(LT), xpos(x), ypos(y), chiffre(ch), r(134), v(6), b(6){}

        void Initialise(int LT, int x, int y, int ch)
        {
            largeur_trait = LT;
            xpos = x;
            ypos = y;
            chiffre = ch;
        }
        void affiche()const;

        int get_xpos()const
        {
            return xpos;
        }
        int get_ypos()const
        {
            return ypos;
        }
        void set_xpos(int x)
        {
            xpos = x;
        }
        void set_ypos(int y)
        {
            ypos = y;
        }
        void set_chiffre(int ch)
        {
            chiffre = ch;
        }
        void set_color(int rouge, int vert, int bleu)
        {
            r = rouge;
            v = vert;
            b = bleu;
        }
};

class Nombre
{
    private:
        SDL_Renderer* renderer;
        int xpos;
        int ypos;
        int largeur_trait;
        int rapportLongLarg = 6;
        std::list<Chiffre> chiffres; //list car souvent push et pop front!
        int nombre;
        int space; // espace entre les chiffres
        int longueur_trait;
    public:
        Nombre(SDL_Renderer* rd, int x, int y, int hauteur, int nbr); // hauteur <==> hauteur de chaque chiffre
        Nombre():renderer(nullptr), xpos(0), ypos(0), largeur_trait(1), rapportLongLarg(2), nombre(0){}
        void operator ++();
        void affiche()const;
        void set_zero();
        void set_color_all(int rouge, int vert, int bleu);
};

#endif
