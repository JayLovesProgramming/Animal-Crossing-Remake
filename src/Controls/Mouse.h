// Controls/Mouse.h
#pragma once

#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"      
#include <iostream>

using std::cout, std::endl;

class MouseManager
{
public:
    static void UpdateMousePosition();

    static void ToggleMouseCursor();

private:
    inline static bool F8_ACTIVE = false;
};
