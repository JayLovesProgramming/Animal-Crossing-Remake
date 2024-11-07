#include "Controls.h"
#include <cmath>
#include "raylib.h"
#include "raymath.h"
#include "Camera/Camera.h"
#include "Map/Ground/Ground.h"
#include "Character/Character.h"
#include "Map/Tree/Tree.h"
#include <iostream>
using std::cout, std::endl;

void GameControls::UpdateControls(Vector3 *characterPos, float characterSpeed)
{
    float deltaSpeed = characterSpeed * GetFrameTime();
    nearTree = false;

    // Calculate directional vectors based on camera rotation (done once)
    float cameraAngle = DEG2RAD * CharacterCamera::cameraRotationAngle;
    Vector3 forwardDirection = {
        sinf(cameraAngle), 
        0.0f, 
        cosf(cameraAngle)
    };
    Vector3 rightDirection = {cosf(cameraAngle), 0.0f, -sinf(cameraAngle)};

    // Normalize the direction vectors
    forwardDirection = Vector3Normalize(forwardDirection);
    rightDirection = Vector3Normalize(rightDirection);

    // Store initial position for collision checking
    Vector3 initialPosition = *characterPos;
    Vector3 newPosition = initialPosition;

    // Movement (forward/backward, left/right)
    if (IsKeyDown(KEY_W))
    {
        newPosition.x -= forwardDirection.x * deltaSpeed;
        newPosition.z -= forwardDirection.z * deltaSpeed;
    }
    if (IsKeyDown(KEY_S))
    {
        newPosition.x += forwardDirection.x * deltaSpeed;
        newPosition.z += forwardDirection.z * deltaSpeed;
    }
    if (IsKeyDown(KEY_A))
    {
        newPosition.x -= rightDirection.x * deltaSpeed;
        newPosition.z -= rightDirection.z * deltaSpeed;
    }
    if (IsKeyDown(KEY_D))
    {
        newPosition.x += rightDirection.x * deltaSpeed;
        newPosition.z += rightDirection.z * deltaSpeed;
    }

    Character::HandleCharacterMovement(newPosition, initialPosition);

    // Boundary checks
    newPosition.x = Clamp(newPosition.x, Map::BOUNDARY_MIN_X, Map::BOUNDARY_MAX_X);
    newPosition.z = Clamp(newPosition.z, Map::BOUNDARY_MIN_Z, Map::BOUNDARY_MAX_Z);

    // Debugging output
    // cout << "Character Position: (" << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << ")\n";

    // Collision detection with trees
    // Collision detection with trees considering both horizontal distance and y-axis position
    for (const auto &treePos : Tree::treePositions)
    {
        // Calculate horizontal distance (ignore y-axis)
        float horizontalDistance = sqrtf((newPosition.x - treePos.x) * (newPosition.x - treePos.x) + (newPosition.z - treePos.z) * (newPosition.z - treePos.z));

        // Calculate vertical distance (y-axis)
        float verticalDistance = fabs(newPosition.y - treePos.y);

        // If within both horizontal and vertical distance thresholds, consider it a collision
        if (horizontalDistance <= Tree::treeCollisionRadius && verticalDistance <= Tree::treeHeightThreshold)
        {
            nearTree = true;
            // Reset position based on attempted movement direction
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S))
            {
                newPosition.z = initialPosition.z;
            }
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
            {
                newPosition.x = initialPosition.x;
            }
            break;
        }
    }

    // Apply movement if no collision detected, ensuring y stays at ground level
    if (!nearTree)
    {
        newPosition.y = 0.0f; // Force Y-axis to ground level
        *characterPos = newPosition;
        animFrameCounter++;
    }
};
