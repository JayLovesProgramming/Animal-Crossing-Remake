// Grass/Grass.h
#pragma once

#include <iostream>
#include "raylib.h"
#include "assert.h"
#include "Debug/Debug.h"

class Grass
{
public:
    Texture2D grassTexture; // Define a texture var for the grassTexture

    Grass()
    {
        LoadGrassTexture(); // Load the grass texture on init
    }

    void LoadGrassTexture(); // Declare the func

    void DEBUG_GrassTexture(bool initial); // Declare the func
    
    ~Grass()
    {
        UnloadTexture(grassTexture); // Unload the texture on destroy
        std::cout << "Destroyed Grass Texture" << std::endl; // Let us know when it's been destroyed
    }
};

