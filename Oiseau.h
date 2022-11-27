//
// Created by justi on 11/11/2022.
//

#ifndef PROJET_FLAPPY_BIRD_OISEAU_H
#define PROJET_FLAPPY_BIRD_OISEAU_H

#include <assert.h>


class Oiseau {
private:
    int pos;
    int pos_hor = 100;
    double vit;
    int rayon = 10; //mettre la bonne valeur
    bool mort_ou_vif = true; //true = vif
    double masse;

public:
    Oiseau(int p, double v, double mass) : pos(p), vit(v), masse(mass){}

    bool monte_ou_descend() {
        if (vit > 0)
            return true;
        return false;
    }

    void oiseau_meurt(bool b) {
        assert(b == true);
        mort_ou_vif = true;
    }

    double get_pos() {
        return pos;
    }

    double get_vit() {
        return vit;
    }

    double get_rayon() {
        return rayon;
    }

    bool get_mort_ou_vif() {
        return mort_ou_vif;
    }

    double get_masse() {
        return masse;
    }

    double get_pos_hor() {
        return pos_hor;
    }

    void set_pos(double p) {
        pos = p;
    }

    void set_vit(double v) {
        vit = v;
    }

};

//Methode pour savoir si il monte ou descend
//Methode mort ou vif
#endif //PROJET_FLAPPY_BIRD_OISEAU_H
