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
#include <cstdlib>
#include <ctime>

#include "Debug/Debug.h"
#include "Menu/ImGui.h"

#include "Map/Grass/Grass.cpp"
#include "Window/Window.cpp"
#include "Camera/Camera.cpp"
#include "Camera/CameraZoom.cpp"
#include "Map/Flower/Flower.cpp"
#include "Map/Tree/Tree.cpp"
#include "Controls/Mouse.cpp"
#include "Controls/Controls.cpp"
#include "Debug/Debug.cpp"
#include "Character/Character.cpp"
#include "Map/Ground/Ground.cpp"
#include "GameState/GameState.cpp"
#include "Menu/Menu.cpp"
#include "Audio/Audio.cpp"
#include "Shader/Shader.cpp"

class Main
{
public:
    static int Run();

private:
    static void EndDrawingLoop();
    static bool InitGame();
    static void UpdatePostDrawLoop();
    static void DrawLoop();
};
