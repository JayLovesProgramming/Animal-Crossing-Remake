#pragma once

#include "raylib.h"

class MouseManager
{
public:
    void UpdateMousePosition()
    {
        Vector2 mousePosition = GetMousePosition();

        if (GetMouseX() < 1)
            SetMousePosition(1, GetMouseY());
        if (GetMouseX() >= GetScreenWidth() - 1)
            SetMousePosition(GetScreenWidth() - 2, GetMouseY());
        if (GetMouseY() < 1)
            SetMousePosition(GetMouseX(), 1);
        if (GetMouseY() >= GetScreenHeight() - 1)
            SetMousePosition(GetMouseX(), GetScreenHeight() - 2);

        SetMousePosition(mousePosition.x, mousePosition.y); // Update cursor position
    }
};

MouseManager mouseManager;
