// Grass/Grass.cpp
#include "Grass.h"

#include <cassert> 
#include <iostream> 
#include "raylib.h" 
#include "Utils/ConsoleOut.h" 

using std::cout, std::endl;

void Grass::LoadGrassTexture()
{
    Grass::grassTexture = LoadTexture("../src/Assets/Textures/grass.png");
    assert(grassTexture.id > 0);
    cout << "[LOADED]: Grass Texture" << endl;
    GenTextureMipmaps(&grassTexture);
    SetTextureFilter(grassTexture, TEXTURE_FILTER_TRILINEAR);
};

void Grass::UnloadGrassTexture()
{
    UnloadTexture(grassTexture);                           // Unload the texture on destroy
    cout << unloadString << "Grass texture" << endl;
}
