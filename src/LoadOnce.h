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

// Potentially place these into CMake? 
#include "Debug/Debug.h"
#include "Map/Grass/Grass.cpp"
#include "Camera/Camera.cpp"
#include "Character/Character.cpp"
#include "Map/Ground/Ground.cpp"
#include "Map/Flower/Flower.cpp"
#include "Map/Tree/Tree.cpp"
#include "Controls/Controls.cpp"
#include "Debug/Debug.cpp"
#include "Camera/CameraZoom.cpp"
#include "Controls/Mouse.cpp"
#include "Menu/Menu.cpp"
#include "Window/Window.cpp"
#include "Audio/Audio.cpp"
#include "Shader/Shader.cpp"
