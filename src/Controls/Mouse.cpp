// Controls/Mouse.cpp
#include "Controls/Mouse.h"

void MouseManager::UpdateMousePosition()
{
    Vector2 windowSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
    Vector2 centerPosition = {windowSize.x / 2, windowSize.y / 2};

    SetMousePosition(static_cast<int>(centerPosition.x), static_cast<int>(centerPosition.y));
}
