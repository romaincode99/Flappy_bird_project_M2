#include <iostream>
#include"Obstacle.h"
#include "Oiseau.h"
#include "Environnement.hpp"
#include <random>


using namespace std;

int main() {
    mt19937 G;
    Environnement<mt19937> JM(G);
    JM.touche_ou_pas();
    cout<<(JM.bird).get_pos()<<endl;
    return 0;
}
