// Controls/Mouse.cpp
#include "Mouse.h"

void MouseManager::UpdateMousePosition()
{
    if (!MouseCursorToggled)
    {
        Vector2 windowSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
        Vector2 centerPosition = {windowSize.x / 2, windowSize.y / 2};
        SetMousePosition(static_cast<int>(centerPosition.x), static_cast<int>(centerPosition.y));
    }
};


void MouseManager::ToggleMouseCursor()
{
    if (IsKeyReleased(KEY_F8))
    {
        MouseCursorToggled = !MouseCursorToggled;
        if (MouseCursorToggled)
        {
            ShowCursor();
        }
        else
        {
            HideCursor();
        }
        std::cout << "TOGGLED F8" << std::endl;
    }
}
