// Character/Character.h
#pragma once

#include "raylib.h"

class Character
{
public:
    constexpr static float characterSpeed = 7.0f;
    static Vector3 characterPosition;

    static void HandleCharacterMovement(Vector3 &characterPosition);
};

Vector3 Character::characterPosition = {0.0f, 1.0f, 0.0f};
