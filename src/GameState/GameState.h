// GameState/GameState.h
#pragma once

#include "Grass/Grass.h"

class GameState
{
public:
    ~GameState()
    {
        Flower::UnloadFlowers();
        Tree::UnloadTrees();
        SurfaceManager::UnloadGround();
        Grass::UnloadGrassTexture();
        CloseWindow(); // Finally close the window
        std::cout << "[DESTROYED]: Game State" << std::endl;
    }
};
