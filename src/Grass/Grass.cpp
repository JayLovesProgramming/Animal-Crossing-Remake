// Grass/Grass.cpp
#include "Grass/Grass.h"

void Grass::DEBUG_GrassTexture(bool initial)
{
    if (initial)
    {
        if (DEBUG_GRASS)
        {
            std::cout << "Grass texture loading" << std::endl;
        }   
    }
    else
    {
        if (DEBUG_GRASS)
        {
            std::cout << "Grass texture loaded successfully" << std::endl;
        }   
    }
}

void Grass::LoadGrassTexture()
{
    Grass::DEBUG_GrassTexture(true);                              
    Grass::grassTexture = LoadTexture("../src/Assets/Textures/grass.png");
    assert(grassTexture.id != 0);      
    Grass::DEBUG_GrassTexture(false);                                
};
