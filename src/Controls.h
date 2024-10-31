// Controls.h
#pragma once

#include "raylib.h"
#include "Camera.h"
#include <cmath>

class GameControls
{
public:
    int animFrameCounter = 0;

    float mapMinX = -50.0f;
    float mapMinZ = -50.0f;

    float mapMaxX = 50.0f;
    float mapMaxZ = 50.0f;

    void UpdateControls(Vector3 *characterPosition, float characterSpeed)
    {
        float deltaSpeed = characterSpeed * GetFrameTime();

        Vector3 forwardDirection = {
            sinf(DEG2RAD * characterCamera.cameraRotationAngle),
            0.0f,
            cosf(DEG2RAD * characterCamera.cameraRotationAngle)
        };

        float forwardLength = sqrtf(forwardDirection.x * forwardDirection.x + forwardDirection.z * forwardDirection.z);
        forwardDirection.x /= forwardLength;
        forwardDirection.z /= forwardLength;

        Vector3 rightDirection = {
            cosf(DEG2RAD * characterCamera.cameraRotationAngle),
            0.0f,
            -sinf(DEG2RAD * characterCamera.cameraRotationAngle)
        };
        
        float rightLength = sqrtf(rightDirection.x * rightDirection.x + rightDirection.z * rightDirection.z);
        rightDirection.x /= forwardLength;
        rightDirection.z /= forwardLength;

        // Forward
        if (IsKeyDown(KEY_W))
        {
            if (characterPosition->z + forwardDirection.z * deltaSpeed <= mapMaxZ)
            {
                characterPosition->z -= forwardDirection.z * deltaSpeed;
                animFrameCounter++;
            }
            // TODO: Fix this collision with trees
            if (characterPosition->x + forwardDirection.x * deltaSpeed <= mapMaxX)
            {
                characterPosition->x -= forwardDirection.x * deltaSpeed;
            }
        }

        // Backward
        if (IsKeyDown(KEY_S))
        {
            if (characterPosition->z - forwardDirection.z * deltaSpeed >= mapMinZ)
            {
                characterPosition->z += forwardDirection.z * deltaSpeed;
                animFrameCounter++;
            }
            // TODO: Fix this collision with trees
            if (characterPosition->x - forwardDirection.x * deltaSpeed >= mapMinX)
            {
                characterPosition->x += forwardDirection.x * deltaSpeed;
            }
        }

        // Left
         if (IsKeyDown(KEY_A))
        {
            if (characterPosition->x + rightDirection.x * deltaSpeed >= mapMinX)
            {
                characterPosition->x -= rightDirection.x * deltaSpeed;
                animFrameCounter++;
            }
            if (characterPosition->z + rightDirection.z * deltaSpeed >= mapMinZ)
            {
                characterPosition->z -= rightDirection.z * deltaSpeed;
            }
        }

        // Right
        if (IsKeyDown(KEY_D))
        {
            if (characterPosition->x - rightDirection.x * deltaSpeed >= mapMinX)
            {
                characterPosition->x += rightDirection.x * deltaSpeed;
                animFrameCounter++;
            }
            if (characterPosition->z - rightDirection.z * deltaSpeed >= mapMinZ)
            {
                characterPosition->z += rightDirection.z * deltaSpeed;
            }
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
