#include "Compteur.hpp"

void Chiffre::affiche_ch(bool haut, bool haut_gauche, bool haut_droite, bool milieu, bool bas_gauche, bool bas_droite, bool bas)const
{
    if(haut)
    {
        SDL_Rect hautrec;
        hautrec.x = xpos + largeur_trait;
        hautrec.y = ypos;
        hautrec.w =  largeur_trait * rapportLongLarg;
        hautrec.h = largeur_trait;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &hautrec);
    }
    if(haut_gauche)
    {
        SDL_Rect haut_gaucherec;
        haut_gaucherec.x = xpos;
        haut_gaucherec.y = ypos + largeur_trait;
        haut_gaucherec.w =  largeur_trait;
        haut_gaucherec.h = largeur_trait * rapportLongLarg;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &haut_gaucherec);
    }
    if(haut_droite)
    {
        SDL_Rect haut_droiterec;
        haut_droiterec.x = xpos + largeur_trait * (rapportLongLarg + 1);
        haut_droiterec.y = ypos + largeur_trait;
        haut_droiterec.w =  largeur_trait;
        haut_droiterec.h = largeur_trait * rapportLongLarg;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &haut_droiterec);
    }
    if(milieu)
    {
        SDL_Rect milieurec;
        milieurec.x = xpos + largeur_trait;
        milieurec.y = ypos + largeur_trait * (rapportLongLarg + 1);
        milieurec.w =  largeur_trait * rapportLongLarg;
        milieurec.h = largeur_trait;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &milieurec);
    }
    if(bas_gauche)
    {
        SDL_Rect bas_gaucherec;
        bas_gaucherec.x = xpos;
        bas_gaucherec.y = ypos + largeur_trait * (rapportLongLarg + 2);
        bas_gaucherec.w =  largeur_trait;
        bas_gaucherec.h = largeur_trait * rapportLongLarg;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &bas_gaucherec);
    }
    if(bas_droite)
    {
        SDL_Rect bas_droiterec;
        bas_droiterec.x = xpos + largeur_trait * (rapportLongLarg + 1);
        bas_droiterec.y = ypos + largeur_trait * (rapportLongLarg + 2);
        bas_droiterec.w =  largeur_trait;
        bas_droiterec.h = largeur_trait * rapportLongLarg;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &bas_droiterec);
    }
    if(bas)
    {
        SDL_Rect basrec;
        basrec.x = xpos + largeur_trait;
        basrec.y = ypos + 2 * largeur_trait * (rapportLongLarg + 1);
        basrec.w =  largeur_trait * rapportLongLarg;
        basrec.h = largeur_trait;
        SDL_SetRenderDrawColor(renderer, r, v, b, 255);
        SDL_RenderFillRect(renderer, &basrec);
    }
}
void Chiffre::affiche()const
{
    if(chiffre == 0)
        affiche_ch(true, true, true, false, true, true, true);
    if(chiffre == 1)
        affiche_ch(false, false, true, false, false, true, false);
    if(chiffre == 2)
        affiche_ch(true, false, true, true, true, false, true);
    if(chiffre == 3)
        affiche_ch(true, false, true, true, false, true, true);
    if(chiffre == 4)
        affiche_ch(false, true, true, true, false, true, false);
    if(chiffre == 5)
        affiche_ch(true, true, false, true, false, true, true);
    if(chiffre == 6)
        affiche_ch(true, true, false, true, true, true, true);
    if(chiffre == 7)
        affiche_ch(true, false, true, false, false, true, false);
    if(chiffre == 8)
        affiche_ch(true, true, true, true, true, true, true);
    if(chiffre == 9)
        affiche_ch(true, true, true, true, false, true, false);
}


//===========================================================================

Nombre::Nombre(SDL_Renderer* rd, int x, int y, int hauteur, int nbr): renderer(rd), xpos(x), ypos(y), nombre(nbr)
{
    largeur_trait = hauteur / (2 * rapportLongLarg + 3);

    std::string chi_str = std::to_string(nbr);
    int chi_int;

    int nbr_chi = chi_str.size();
    longueur_trait =   rapportLongLarg * largeur_trait;
    space = 3 * largeur_trait;
    std::cout<<space<<std::endl;

    chiffres = std::list<Chiffre>(nbr_chi, renderer);
    int i =0;
    for(auto& CHI : chiffres)
    {
        std::from_chars(chi_str.c_str() + i, chi_str.c_str() + i + 1, chi_int);
        if(i == 0)
        CHI.Initialise(largeur_trait, xpos + i * longueur_trait, ypos, chi_int);
        else
        CHI.Initialise(largeur_trait, xpos + i * longueur_trait + space, ypos, chi_int); // std::stoi retranscrit le string "3" en int 3
        ++i;
    }
}

void Nombre::operator ++()
{
    int chi_int;
    std::string AVchi_str = std::to_string(nombre);
    int AVtaille = AVchi_str.size();
    nombre++;
    std::string APchi_str = std::to_string(nombre);
    int APtaille = APchi_str.size();

    if(AVtaille == APtaille)
    {
        std::from_chars(APchi_str.c_str() + APtaille - 1, APchi_str.c_str() + APtaille, chi_int);
        auto it = chiffres.end(); --it;
        it -> set_chiffre(chi_int);
        if(chi_int == 0)
        {
            int i = 1;
            while(chi_int == 0)
            {
                it -> set_chiffre(0);
                std::from_chars(APchi_str.c_str() + APtaille - i - 1, APchi_str.c_str() + APtaille - i, chi_int);
                --it;
                ++i;
            }
            it -> set_chiffre(chi_int);
        }
    }
    else
    {
        Chiffre ZERO(renderer, largeur_trait, xpos, ypos, 0);
        Chiffre UN(renderer, largeur_trait, xpos, ypos, 1);
        int position = xpos;
        for(auto& C : chiffres)
        {
            position = C.get_xpos() + longueur_trait + space;
            ZERO.set_xpos(position);
            C = ZERO;
        }
        chiffres.push_front(UN);
    }
}

void Nombre::set_zero()
{
    chiffres.clear();
    nombre = 0;
    Chiffre ZERO(renderer, largeur_trait, xpos, ypos, 0);
    chiffres.push_back(ZERO);
}
void Nombre::affiche()const
{
    for(auto& CHI : chiffres)
        CHI.affiche();
}

void Nombre::set_color_all(int rouge, int vert, int bleu)
{
    for(auto& Nb : chiffres)
        Nb.set_color(rouge, vert, bleu);
}
