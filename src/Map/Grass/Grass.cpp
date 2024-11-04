// Grass/Grass.cpp
#include "Grass.h"


void Grass::LoadGrassTexture()
{
    Grass::grassTexture = LoadTexture("../src/Assets/Textures/grass.png");
    assert(grassTexture.id > 0);
    std::cout << "[LOADED]: Grass Texture" << std::endl;
    GenTextureMipmaps(&grassTexture);
    SetTextureFilter(grassTexture, TEXTURE_FILTER_TRILINEAR);
};

void Grass::UnloadGrassTexture()
{
    UnloadTexture(grassTexture);                           // Unload the texture on destroy
    std::cout << "[UNLOADED]: Grass Texture" << std::endl; // Let us know when it's been destroyed
}
