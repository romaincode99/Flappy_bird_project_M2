#include "Graphique.hpp"
#include "JeuExpt.hpp"
#include <SDL2/SDL.h>
#include <random>
#include <stdio.h>
#include <ctime>

using namespace std;

int main()
{
  mt19937 G(time(NULL));
  Jeu J(G);
  Jeu.En
  J.run();

  return 0;
}
