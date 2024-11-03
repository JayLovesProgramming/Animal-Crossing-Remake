// GameState/GameState.h
#pragma once

#include <iostream>
#include "raylib.h"
#include "Map/Map.h"

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
        std::cout << "Unloaded Ground Surface" << std::endl;
    };

    ~GameState()
    {
        CloseWindow(); // Finally close the window
        UnloadGroundSurface();
        std::cout << "Destroyed Game State" << std::endl;
    }
};

GameState state;
