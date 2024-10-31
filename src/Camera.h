#pragma once

#include "raylib.h"

class CharacterCamera
{
    public:
    Camera camera = {0};
    constexpr static float cameraDistance = 15.0f;
    constexpr static float turningModifier = 8.0f;
    float cameraRotationAngle = 0.0f;

    void InitCamera()
    {
        camera.position = Vector3{0.0f, 5.0f, 10.0f}; // Camera position
        camera.target = Vector3{0.0f, 1.0f, 0.0f};    // Looking at the character
        camera.up = Vector3{0.0f, 1.0f, 0.0f};        // Camera up vector
        camera.fovy = 42.0f;                            // Field of view
        camera.projection = CAMERA_PERSPECTIVE; //CAMERA_ORTHOGRAPHIC for a more top view
    }

    void UpdateCamera(Vector3 *characterPosition)
    {
        if (IsKeyDown(KEY_LEFT)) {
            cameraRotationAngle -= turningModifier; // Rotate left
        }
        if (IsKeyDown(KEY_RIGHT)) {
            cameraRotationAngle += turningModifier; // Rotate right
        }
        camera.position.x = characterPosition->x + cameraDistance * sinf(DEG2RAD * cameraRotationAngle);
        camera.position.z = characterPosition->z + cameraDistance * cosf(DEG2RAD * cameraRotationAngle);
        camera.position.y = characterPosition->y + 3.5f;
        camera.target = *characterPosition;
    }
};

CharacterCamera characterCamera;
