// Camera.h
#pragma once

#include "raylib.h"

class CharacterCamera
{
public:
    Camera camera = {0};
    constexpr static float cameraDistance = 15.0f;
    constexpr static float turningModifier = 1.0f;
    float cameraRotationAngle = 0.0f;

    void InitCamera()
    {
        camera.position = Vector3{0.0f, 5.0f, 10.0f}; // Camera position
        camera.target = Vector3{0.0f, 1.0f, 0.0f};    // Looking at the character
        camera.up = Vector3{0.0f, 1.0f, 0.0f};        // Camera up vector
        camera.fovy = 42.0f;                          // Field of view
        camera.projection = CAMERA_PERSPECTIVE;       // CAMERA_ORTHOGRAPHIC for a more top view
    }

    void UpdateCamera(Vector3 *characterPosition)
    {
        if (IsKeyDown(KEY_LEFT) || GetMouseDelta().x < 0)
        {
            cameraRotationAngle += turningModifier; // Rotate left
        }
        else if (IsKeyDown(KEY_RIGHT) || GetMouseDelta().x > 0)
        {
            cameraRotationAngle -= turningModifier; // Rotate right
        }

        Vector3 forwardDirection = {
            sinf(DEG2RAD * cameraRotationAngle),
            0.0f,
            cosf(DEG2RAD * cameraRotationAngle)};

        float forwardLength = (forwardDirection.x * forwardDirection.x) + (forwardDirection.z * forwardDirection.z);
        forwardDirection.x /= forwardLength;
        forwardDirection.z /= forwardLength;

        camera.position.x = characterPosition->x + cameraDistance * forwardDirection.x;
        camera.position.z = characterPosition->z + cameraDistance * forwardDirection.z;
        camera.position.y = characterPosition->y + 3.5f;
        camera.target = *characterPosition;
    }
};

CharacterCamera characterCamera;
