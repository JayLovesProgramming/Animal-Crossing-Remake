// GameState/GameState.h
#pragma once

#include "Map/Grass/Grass.h" 
#include "Map/Ground/Ground.h" 
#include "Map/Flower/Flower.h" 
#include "Map/Tree/Tree.h" 
#include <iostream> 

using std::cout, std::endl;

class GameState
{
public:
    ~GameState();
};

GameState state;
