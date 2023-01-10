#ifndef PROJET_FLAPPY_BIRD_OISEAU_H
#define PROJET_FLAPPY_BIRD_OISEAU_H

#include <assert.h>


class Oiseau {
private:
    double pos;
    int pos_hor = 100;
    double vit;
    int rayon;
    bool mort_ou_vif = true; //true = vif

public:
    Oiseau(int p, double v, int r) : pos(p), vit(v), rayon(r){}

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
