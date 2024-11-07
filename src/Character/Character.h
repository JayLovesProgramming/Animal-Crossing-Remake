// Character/Character.h
#pragma once

using std::cout, std::endl;

class Character
{
public:
    constexpr static float characterSpeed = 7.0f;
    inline static Vector3 characterPos = {0.0f, 1.0f, 0.0f};
    inline static Vector3 position = {0.0f, 0.0f, 0.0f}; // Set model pos
    
    inline static Model model;

    // TODO: Make this a relative path
    inline static const char *modelPath = "C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Models/robot.glb";
    
    inline static ModelAnimation *modelAnimations;
    inline static int animsCount = 0;
    inline static unsigned int animIndex = 6;
    inline static unsigned int animCurrentFrame = 0;

    static void LoadCharacterModel();

    static void CharacterWalk(bool isWalking);

    static void DrawCharacter();

    // DEBUG - Soon to remove
    static inline bool printedCurrentAnim = false;
};
