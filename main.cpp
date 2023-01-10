#include "Jeu.hpp"
#include <SDL2/SDL.h>
#include <random>
#include <stdio.h>
#include <ctime>
#include<iostream>

using namespace std;

//int main()
int main(int argc, char *argv[])
{
    mt19937 G(time(NULL));
    Jeu<mt19937> J(G);
    J.run();
    return 0;
}

