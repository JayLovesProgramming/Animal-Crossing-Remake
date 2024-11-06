// GameState/GameState.cpp
#include "GameState.h"

GameState::~GameState()
{
    Flower::UnloadFlowers();
    Tree::UnloadTrees();
    Map::UnloadGround();
    Grass::UnloadGrassTexture();
    CloseWindow(); // Finally close the window
    std::cout << "[DESTROYED]: Game State" << std::endl;
}
