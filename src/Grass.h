// Grass.h
#pragma once

#include <iostream>
#include "raylib.h"
#include "assert.h"
#include "Debug.h"

class Grass
{
public:
    Texture2D grassTexture; 

    Grass()
    {
        LoadGrassTexture();
    }

    void LoadGrassTexture();

    void DEBUG_GrassTexture(bool initial);
};
