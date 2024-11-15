#include "Controls.h"
#include <cmath>
#include "raylib.h"
#include "raymath.h"
#include "Camera/Camera.h"
#include "Map/Ground/Ground.h"
#include "Map/Tree/Tree.h"
#include "Map/Flower/Flower.h"
#include "Character/Character.h"
#include "Audio/Audio.h"
#include <iostream>
using std::cout, std::endl;

void GameControls::HandleNearbyObjectCollisions()
{
    Tree::HandleTreeCollision();
    Flower::HandleFlowerCollision();
}

void GameControls::HandleCameraPerspective()
{
    if (IsKeyReleased(KEY_F5))
    {
        CharacterCamera::camera.projection = (CharacterCamera::camera.projection == CAMERA_ORTHOGRAPHIC) ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC;
    }
}

void GameControls::UpdateControls(Vector3 *characterPos, float &characterSpeed)
{
    float deltaSpeed = characterSpeed * GetFrameTime();

    // Calculate directional vectors based on camera rotation (done once)
    float cameraAngle = DEG2RAD * CharacterCamera::cameraRotationAngle;
    Vector3 forwardDirection = {
        sinf(cameraAngle),
        0.0f,
        cosf(cameraAngle)};
    Vector3 rightDirection = {
        cosf(cameraAngle),
        0.0f,
        -sinf(cameraAngle)};

    // Normalize the direction vectors
    forwardDirection = Vector3Normalize(forwardDirection);
    rightDirection = Vector3Normalize(rightDirection);

    // Store initial position for collision checking
    initialPosition = *characterPos; // ? WTF is this doing
    newPosition = initialPosition;

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

    if (IsKeyPressed(KEY_SPACE) && !isJumping)
    {
        isJumping = true;
        verticalVelocity = jumpForce;
    }

    if (isJumping)
    {
        // Apply upward movement and gravity
        newPosition.y += verticalVelocity * GetFrameTime();
        verticalVelocity -= gravity * GetFrameTime();

        // Check if character has landed
        if (newPosition.y <= 0.0f)
        {
            newPosition.y = 0.0f;
            isJumping = false;
            verticalVelocity = 0.0f;
            AudioManager::PlayACoolSoundThing("JumpSound");
        }
    }
    else
    {
        newPosition.y = 0.0f; // Force Y-axis to ground level
    }

    Character::HandleCharacterMovement(newPosition, initialPosition);

    // Boundary checks
    newPosition.x = Clamp(newPosition.x, Map::BOUNDARY_MIN_X, Map::BOUNDARY_MAX_X);
    newPosition.z = Clamp(newPosition.z, Map::BOUNDARY_MIN_Z, Map::BOUNDARY_MAX_Z);

    // Debugging output
    // cout << "Character Position: (" << newPosition.x << ", " << newPosition.y << ", " << newPosition.z << ")\n";

    HandleNearbyObjectCollisions();

    // Apply movement if no collision detected, ensuring y stays at ground level
    if (nearFlower && Character::defaultCharacterSpeed <= Character::characterSpeed && ( Character::characterSpeed <= Character::defaultCharacterSpeed + 3)) // i felt like being magic
    {
        characterSpeed += 0.65f * deltaSpeed;
    }
    else
    {
        characterSpeed = Character::defaultCharacterSpeed;
    }


    if (!nearTree)
    {
        *characterPos = newPosition;
        animFrameCounter++;
    }
};
