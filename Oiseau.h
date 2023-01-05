//
// Created by justi on 11/11/2022.
//

#ifndef PROJET_FLAPPY_BIRD_OISEAU_H
#define PROJET_FLAPPY_BIRD_OISEAU_H

#include <assert.h>


class Oiseau {
private:
    double pos;
    int pos_hor = 100;
    double vit;
    int rayon; //mettre la bonne valeur
    bool mort_ou_vif = true; //true = vif
    double masse;

public:
    Oiseau(int p, double v, double mass, int r) : pos(p), vit(v), masse(mass), rayon(r){}

    bool monte_ou_descend()const
    {
        if (vit > 0)
            return true;
        return false;
    }

    void oiseau_meurt(bool b)
    {
        assert(b == true);
        mort_ou_vif = true;
    }

    double get_pos()const
    {
        return pos;
    }

    double get_vit()const {
        return vit;
    }

    int get_rayon()const {
        return rayon;
    }

/*    bool get_mort_ou_vif() const{
        return mort_ou_vif;
    }*/

    double get_masse()const {
        return masse;
    }

    int get_pos_hor()const {
        return pos_hor;
    }

    void set_pos(double p) {
        pos = p;
    }

    void set_vit(double v) {
        vit = v;
    }

};

#endif //PROJET_FLAPPY_BIRD_OISEAU_H
