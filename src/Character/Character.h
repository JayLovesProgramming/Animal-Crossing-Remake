// Character/Character.h
#pragma once

#include "raylib.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Ground/Ground.h" // TEMP TO DISABLE RED SQUIGGLY LINES

class Character
{
public:
    constexpr static float characterSpeed = 7.0f;
    inline static Vector3 characterPosition = {0.0f, 1.0f, 0.0f};

    static void HandleCharacterMovement();
};
