// Character/Character.h
#pragma once

using std::cout, std::endl;

class Character
{
public:
    constexpr static float characterSpeed = 7.0f;
    inline static Vector3 characterPos = {0.0f, 1.0f, 0.0f};

    static void HandleCharacterMovement();

    static struct CharacterPosition
    {
        float mapRotation;
        float groundHeight;
    } CalculateCharacterPos();

};
