// Grass/Grass.h
#pragma once

class Grass
{
public:
    inline static Texture2D grassTexture; // Define a texture var for the grassTexture

    static void LoadGrassTexture(); // Declare the func

    static void UnloadGrassTexture();
};

