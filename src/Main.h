// Main.h
#pragma once

#include "raylib.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <assert.h>

#include "rlgl.h"
#include "Window/Window.cpp"
#include "Camera/Camera.cpp"
#include "Flower/Flower.cpp"
#include "Tree/Tree.cpp"
#include "Controls/Mouse.cpp"
#include "Controls/Controls.cpp"
#include "Debug/Debug.cpp"
#include "Character/Character.cpp"
#include "Map/Map.cpp"
#include "GameState/GameState.cpp"
#include "UI/UI.cpp"
#include "Grass/Grass.cpp"


class Main
{
public:
    static int Run();

private:
    static void EndDrawingLoop();
    static bool InitGame();
    static void UpdatePostDrawLoop();
    static void DrawLoop(Vector3& characterPosition, SurfaceManager grounds[SurfaceManager::GRID_SIZE][SurfaceManager::GRID_SIZE]);
};
