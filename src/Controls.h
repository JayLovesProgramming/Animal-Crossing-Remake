#pragma once

#include "raylib.h"
#include <cmath>

class GameControls
{
public:
    int animFrameCounter = 0;
    float mapMinX = -50.0f;
    float mapMaxX = 50.0f;
    float mapMinZ = -50.0f;
    float mapMaxZ = 50.0f;

    void UpdateControls(Vector3 *characterPosition, float characterSpeed)
    {
        float deltaSpeed = characterSpeed * GetFrameTime();

        if (IsKeyDown(KEY_W) && characterPosition->z - deltaSpeed >= mapMinZ)
        {
            characterPosition->z -= deltaSpeed;
            animFrameCounter++;
        }
        if (IsKeyDown(KEY_S) && characterPosition->z + deltaSpeed <= mapMaxZ)
        {
            characterPosition->z += deltaSpeed;
            animFrameCounter++;
        }
        if (IsKeyDown(KEY_A) && characterPosition->x - deltaSpeed >= mapMinX)
        {
            characterPosition->x -= deltaSpeed;
            animFrameCounter++;
        }
        if (IsKeyDown(KEY_D) && characterPosition->x + deltaSpeed <= mapMaxX)
        {
            characterPosition->x += deltaSpeed;
            animFrameCounter++;
        }

        for (int i = 0; i < trees.treePositions.size(); i++)
        {
            const Vector3 &treePos = trees.treePositions[i];
            float distance = sqrtf(powf(characterPosition->x - treePos.x, 2) + powf(characterPosition->y - treePos.y, 2) + powf(characterPosition->z - treePos.z, 2));
            if (distance < trees.treeCollisionRadius)
            {
                if (IsKeyDown(KEY_W) && characterPosition->z + deltaSpeed <= mapMaxZ)
                    characterPosition->z += deltaSpeed;
                if (IsKeyDown(KEY_S) && characterPosition->z - deltaSpeed >= mapMinZ)
                    characterPosition->z -= deltaSpeed;
                if (IsKeyDown(KEY_A) && characterPosition->x + deltaSpeed <= mapMaxX)
                    characterPosition->x += deltaSpeed;
                if (IsKeyDown(KEY_D) && characterPosition->x - deltaSpeed >= mapMinX)
                    characterPosition->x -= deltaSpeed;
            }
        }
    }
};

GameControls gameControls;
