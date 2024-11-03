// Grass/Grass.cpp
#include "Grass/Grass.h"

void Grass::LoadGrassTexture()
{
    Grass::grassTexture = LoadTexture("../src/Assets/Textures/grass.png");
    assert(grassTexture.id != 0);
    std::cout << "[LOADED]: Grass Texture" << std::endl;
};

void Grass::UnloadGrassTexture()
{
    UnloadTexture(grassTexture);                           // Unload the texture on destroy
    std::cout << "[UNLOADED]: Grass Texture" << std::endl; // Let us know when it's been destroyed
}
