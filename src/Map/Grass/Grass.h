// Grass/Grass.h
#pragma once

struct Grass
{
    inline static Texture2D grassTexture; // Define a texture var for the grassTexture

    static void LoadGrassTexture(); // Load the grass texture
    static void UnloadGrassTexture(); // Unload the grass texture
};

