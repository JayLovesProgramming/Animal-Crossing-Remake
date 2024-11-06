// Grass/Grass.h
#pragma once

#include <cassert> // TEMP TO DISABLE RED SQUIGGLY LINES
#include <iostream> // TEMP TO DISABLE RED SQUIGGLY LINES
#include "raylib.h" // TEMP TO DISABLE RED SQUIGGLY LINES

using std::cout, std::endl;

class Grass
{
public:
    inline static Texture2D grassTexture; // Define a texture var for the grassTexture

    static void LoadGrassTexture(); // Declare the func

    static void UnloadGrassTexture();
};

