// Controls/Controls.h
#pragma once

#include <cmath>
#include "raylib.h"
#include "Camera/Camera.h"
#include "Map/Map.h"
#include "Tree/Tree.h"

class GameControls
{
public:
    int animFrameCounter = 0;

    void UpdateControls(Vector3 *characterPosition, float characterSpeed)
    {
        float deltaSpeed = characterSpeed * GetFrameTime();

        Vector3 forwardDirection = {
            sinf(DEG2RAD * characterCamera.cameraRotationAngle),
            0.0f,
            cosf(DEG2RAD * characterCamera.cameraRotationAngle)};

        Vector3 rightDirection = {
            cosf(DEG2RAD * characterCamera.cameraRotationAngle),
            0.0f,
            -sinf(DEG2RAD * characterCamera.cameraRotationAngle)};

        float forwardLength = sqrtf(forwardDirection.x * forwardDirection.x + forwardDirection.z * forwardDirection.z);
        forwardDirection.x /= forwardLength;
        forwardDirection.z /= forwardLength;

        float rightLength = sqrtf(rightDirection.x * rightDirection.x + rightDirection.z * rightDirection.z);
        rightDirection.x /= rightLength;
        rightDirection.z /= rightLength;

        Vector3 newPosition = *characterPosition;

        // Store initial position for collision checking
        Vector3 initialPosition = *characterPosition;

        // Forward
        if (IsKeyDown(KEY_W))
        {
            newPosition.z -= forwardDirection.z * deltaSpeed;
            newPosition.x -= forwardDirection.x * deltaSpeed;
        }

        // Backward
        if (IsKeyDown(KEY_S))
        {
            newPosition.z += forwardDirection.z * deltaSpeed;
            newPosition.x += forwardDirection.x * deltaSpeed;
        }

        // Left
        if (IsKeyDown(KEY_A))
        {
            newPosition.x -= rightDirection.x * deltaSpeed;
            newPosition.z -= rightDirection.z * deltaSpeed;
        }

        // Right
        if (IsKeyDown(KEY_D))
        {
            newPosition.x += rightDirection.x * deltaSpeed;
            newPosition.z += rightDirection.z * deltaSpeed;
        }

        // Bound checks
        if (newPosition.x < BOUNDARY_MIN_X)
            newPosition.x = BOUNDARY_MIN_X;
        if (newPosition.x > BOUNDARY_MAX_X)
            newPosition.x = BOUNDARY_MAX_X;
        if (newPosition.z < BOUNDARY_MIN_Z)
            newPosition.z = BOUNDARY_MIN_Z;
        if (newPosition.z > BOUNDARY_MAX_Z)
            newPosition.z = BOUNDARY_MAX_Z;

        // Check for collisions with trees
        bool canMove = true;
        for (const auto &treePos : Tree::treePositions)
        {
            float distance = sqrtf(powf(newPosition.x - treePos.x, 2) + powf(newPosition.y - treePos.y, 2) + powf(newPosition.z - treePos.z, 2));
            if (distance < Tree::treeCollisionRadius)
            {
                canMove = false;

                // Check if the character is trying to move into the tree
                if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S))
                {
                    newPosition.z = initialPosition.z; // Reset Z position
                }
                if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
                {
                    newPosition.x = initialPosition.x; // Reset X position
                }
                break; // No need to check further trees
            }
        }

        // Apply movement if no collision detected
        if (canMove)
        {
            *characterPosition = newPosition;
            animFrameCounter++;
        }
    }
};

GameControls gameControls;
