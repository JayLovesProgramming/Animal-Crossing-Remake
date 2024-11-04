// Grass/Grass.h
#pragma once

class Grass
{
public:
    static Texture2D grassTexture; // Define a texture var for the grassTexture

    static void LoadGrassTexture(); // Declare the func

    static void UnloadGrassTexture();
};

Texture2D Grass::grassTexture;
