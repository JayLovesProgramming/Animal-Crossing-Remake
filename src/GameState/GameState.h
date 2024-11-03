// GameState/GameState.h
#pragma once

#include <iostream>
#include "raylib.h"
#include "Map/Map.h"
#include "Tree/Tree.h"
#include "Flower/Flower.h"
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

GameState state;
