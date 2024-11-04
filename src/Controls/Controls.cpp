#include "Controls.h"



void GameControls::UpdateControls(Vector3 *characterPosition, float characterSpeed)
{
    float deltaSpeed = characterSpeed * GetFrameTime();
    nearTree = false;

    // Set fixed ground level
    const float groundLevel = 0.0f;

    // Calculate directional vectors based on camera rotation
    Vector3 forwardDirection = {
        sinf(DEG2RAD * CharacterCamera::cameraRotationAngle),
        0.0f,
        cosf(DEG2RAD * CharacterCamera::cameraRotationAngle)};
        
    Vector3 rightDirection = {
        cosf(DEG2RAD * CharacterCamera::cameraRotationAngle),
        0.0f,
        -sinf(DEG2RAD * CharacterCamera::cameraRotationAngle)};

    // Normalize forward and right vectors
    forwardDirection = Vector3Normalize(forwardDirection);
    rightDirection = Vector3Normalize(rightDirection);

    // Store initial position for collision checking and movement
    Vector3 newPosition = *characterPosition;
    // newPosition.y = groundLevel; // Ensure Y-axis stays at ground level

    Vector3 initialPosition = *characterPosition;

    // Forward and backward movement
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

    // Left and right movement
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

  

    //Boundary checks
    newPosition.x = Clamp(newPosition.x, Map::BOUNDARY_MIN_X, Map::BOUNDARY_MAX_X);
    newPosition.z = Clamp(newPosition.z, Map::BOUNDARY_MIN_Z, Map::BOUNDARY_MAX_Z);
    // std::cout << "X: " << newPosition.x << " Y: " << newPosition.y << std::endl;
    
    // Collision detection with trees
    for (const auto &treePos : Tree::treePositions) 
    {
        float distance = Vector3Distance(newPosition, treePos);
        if (distance <= Tree::treeCollisionRadius) 
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
        newPosition.y = groundLevel; // Force Y-axis to ground level
        *characterPosition = newPosition;
        animFrameCounter++;
    }
};
