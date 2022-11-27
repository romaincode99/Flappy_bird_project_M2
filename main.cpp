// #include <iostream>
// #include"Obstacle.h"
// #include "Oiseau.h"
// #include "Environement.hpp"
#include "Graphique.hpp"

using namespace std;

int main()
{
  Graphique A(300,300);
  bool run=true;
  while(run){
    A.ecouter();
    if(A.get_quitter()){
      run=false;
    }
    if(A.get_touche_enfoncee()){
      cout << "A.touche_appuyee" << endl;
    }
    SDL_Delay(10);
  }

  return 0;
}
