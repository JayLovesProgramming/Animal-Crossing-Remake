#include "Grass.h"

void Grass::LoadGrassTexture()
{
    Grass::grassTexture = LoadTexture("../src/Assets/Textures/grass.png");
    assert(grassTexture.id != 0);                                                          
};
