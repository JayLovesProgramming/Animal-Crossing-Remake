#pragma once

#include "raylib.h"
#include "Map/Map.h"

class CharacterCamera
{
public:
    Camera camera = {0};
    float cameraDistance = 15.0f;
    float cameraRotationAngle = 0.0f;
    constexpr static float turningModifier = 20.5f;

    void InitCamera()
    {
        camera.position = Vector3{0.0f, 0.0f, 0.0f}; // Camera position
        camera.target = Vector3{0.0f, 0.0f, 0.0f};   // Looking at the character
        camera.up = Vector3{0.0f, 1.0f, 0.0f};       // Camera up vector
        camera.fovy = 35.0f;                         // Field of view
        camera.projection = CAMERA_PERSPECTIVE;      // CAMERA_ORTHOGRAPHIC for a more top view
    }

    void UpdateCameraModeProjection()
    {
        if (IsKeyReleased(KEY_F5))
        {
            camera.projection = (camera.projection == CAMERA_ORTHOGRAPHIC) ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC;
        }
    }

    void UpdateCameraZoom()
    {
        static float targetCameraDistance = cameraDistance;
        float zoomSpeed = 1.5f;
        float minCameraDistance = 10.0f; // Minimum zoom level
        float maxCameraDistance = 20.0f; // Maximum zoom level
        float smoothFactor = 0.1f;       // Adjust this for smoother or faster transitions

        float mouseWheelMove = GetMouseWheelMove();

        if (mouseWheelMove != 0)
        {
            targetCameraDistance -= mouseWheelMove * zoomSpeed;

            targetCameraDistance = Clamp(targetCameraDistance, minCameraDistance, maxCameraDistance);
        }

        cameraDistance += (targetCameraDistance - cameraDistance) * smoothFactor;
    }

    void UpdateCamera(Vector3 *characterPosition)
    {
        UpdateCameraZoom();
        UpdateCameraModeProjection();

        float targetAngle = cameraRotationAngle;

        Vector2 mouseDelta = GetMouseDelta();
        float rotationInput = 0.0f;

        if (IsKeyDown(KEY_LEFT))
            rotationInput += turningModifier;
        if (IsKeyDown(KEY_RIGHT))
            rotationInput -= turningModifier;

        rotationInput += (mouseDelta.x < 0) ? turningModifier : (mouseDelta.x > 0) ? -turningModifier : 0;

        targetAngle += rotationInput;
        cameraRotationAngle += (targetAngle - cameraRotationAngle) * 0.1f;

        Vector3 forwardDirection = {
            sinf(DEG2RAD * cameraRotationAngle),
            0.0f,
            cosf(DEG2RAD * cameraRotationAngle)};

        float forwardLength = Vector3Length(forwardDirection);
        if (forwardLength != 0)
        {
            forwardDirection.x /= forwardLength;
            forwardDirection.z /= forwardLength;
        }

        camera.position.x = characterPosition->x + cameraDistance * forwardDirection.x;
        camera.position.z = characterPosition->z + cameraDistance * forwardDirection.z;

        camera.position.y = surfaceManager.GetHeightAtPosition(camera.position.x, camera.position.z) + 3.5f; // Maintain height above the surface

        camera.target = *characterPosition; // Always look at the character
    }
};

CharacterCamera characterCamera;
