// GameState/GameState.cpp
#include "GameState.h"

GameState::~GameState()
{
    Flower::UnloadFlowers();
    Tree::UnloadTrees();
    Map::UnloadGround();
    Grass::UnloadGrassTexture();
    AudioManager::UnloadAudio();
    Character::UnloadCharacterModel();
    CloseWindow(); // Finally close the window
    std::cout << destroyedString << "Game State" << std::endl;
}
