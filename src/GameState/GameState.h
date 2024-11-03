// GameState/GameState.h
#pragma once

#include <iostream>
#include "raylib.h"
#include "Map/Map.h"
#include "Tree/Tree.h"
#include "Flower/Flower.h"

SurfaceManager grounds[GRID_SIZE][GRID_SIZE];

class GameState
{
public:
    static void UnloadGroundSurface()
    {
        // TODO: Ensure the ground is unloaded properly
        // Unload the ground
        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int z = 0; z < GRID_SIZE; z++)
            {
                UnloadModel(grounds[x][z].model);
            }
        }
        std::cout << "[UNLOADED]: Ground Surface" << std::endl;
    };

    ~GameState()
    {   
        Flower::UnloadFlowers();
        Tree::UnloadTrees();
        UnloadGroundSurface();
        CloseWindow(); // Finally close the window
        std::cout << "[DESTROYED]: Game State" << std::endl;
    }
};

GameState state;
