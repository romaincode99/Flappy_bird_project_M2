#include "cls.hpp"
#include <iostream>
#include "Oiseau.h"
#include "Environnement.hpp"
#include <random>

int main()
{
  mt19937 G;
  Environnement<mt19937> A(G);
  A.avance_oiseau();
  std::cout <<A.get_oiseau().get_pos()<< '\n';
  A.avance_oiseau();
  std::cout <<A.get_oiseau().get_pos()<< '\n';
}
