// Main.h
#pragma once

#include "raylib.h"
#include "rlgl.h"
// So the compiler compiles Main.cpp and when the compiler sees #include "raylib.h" for example, then it replaces the #include line with the contents of that file hence why some other cpp files do not require raylib etc

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <string>
#include <assert.h>
#include <cstdlib>
#include <ctime>
#include <cassert>

#include "Debug/Debug.h"

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
    static void HandleCharacterMovement(Vector3 &characterPosition);
    static void DrawLoop(Vector3& characterPosition, SurfaceManager grounds[SurfaceManager::GRID_SIZE][SurfaceManager::GRID_SIZE]);
};
