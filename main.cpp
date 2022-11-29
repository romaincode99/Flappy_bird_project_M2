// #include <iostream>
// #include"Obstacle.h"
// #include "Oiseau.h"
// #include "Environement.hpp"
#include "Graphique.hpp"
#include "Jeu.hpp"
#include <SDL2/SDL.h>
#include <random>
#include <stdio.h>
#include <ctime>

using namespace std;

int main()
{
  mt19937 G(time(NULL));
  Jeu J(G);
  J.run();

  return 0;
}

//rajouter le faite que si on appui long temsp le soisseua saute plus haut !!
// faire attention au centre de l'oiseau !
// faire test unitaires
