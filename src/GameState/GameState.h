// GameState/GameState.h
#pragma once

#include "Map/Grass/Grass.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Ground/Ground.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Flower/Flower.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Tree/Tree.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include <iostream> // TEMP TO DISABLE RED SQUIGGLY LINES

using std::cout, std::endl;

class GameState
{
public:
    ~GameState();
};

GameState state;
