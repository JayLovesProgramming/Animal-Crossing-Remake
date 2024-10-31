#include "Grass.h"

void Grass::LoadGrassTexture()
{
    if (DEBUG_GRASS)
    {
        std::cout << "Loading grass texture" << std::endl;
    }   
    Grass::grassTexture = LoadTexture("../src/Assets/Textures/grass.png");
    assert(grassTexture.id != 0);        
    if (DEBUG_GRASS)
    {
        std::cout << "Grass texture loaded" << std::endl;
    }                                                  
};
