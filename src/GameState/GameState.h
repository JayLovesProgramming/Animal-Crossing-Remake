// GameState/GameState.h
#pragma once

#include "Map/Grass/Grass.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Ground/Ground.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Flower/Flower.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Tree/Tree.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include <iostream> // TEMP TO DISABLE RED SQUIGGLY LINES

class GameState
{
public:
     ~GameState()
    {
        Flower::UnloadFlowers();
        Tree::UnloadTrees();
        Map::UnloadGround();
        Grass::UnloadGrassTexture();
        CloseWindow(); // Finally close the window
        std::cout << "[DESTROYED]: Game State" << std::endl;
    };
};

GameState state;
