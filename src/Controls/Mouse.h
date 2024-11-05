// Controls/Mouse.h
#pragma once

#include "raylib.h"
#include "raymath.h"
#include "imgui.h"
#include "rlImGui.h"      
#include <iostream>

class MouseManager
{
public:
    inline static bool F8_ACTIVE = false;

    static void UpdateMousePosition();

    static void ToggleMouseCursor();


    
};
