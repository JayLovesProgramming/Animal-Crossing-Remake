// Camera/Camera.h
#pragma once

#include "raylib.h"
#include "Map/Map.h"

class CharacterCamera
{
public:
    static Camera camera;
    static float cameraRotationAngle;

    static void InitCamera()
    {
        camera.position = Vector3{0.0f, 0.0f, 0.0f}; // Camera position
        camera.target = Vector3{0.0f, 0.0f, 0.0f};   // Looking at the character
        camera.up = Vector3{0.0f, 1.0f, 0.0f};       // Camera up vector
        camera.fovy = 35.0f;                         // Field of view
        camera.projection = CAMERA_PERSPECTIVE;      // CAMERA_ORTHOGRAPHIC for a more top view
    }

    static void UpdateCameraModeProjection()
    {
        if (IsKeyReleased(KEY_F5))
        {
            camera.projection = (camera.projection == CAMERA_ORTHOGRAPHIC) ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC;
        }
    }
    static void UpdateCameraZoom()
    {
        static float targetCameraDistance = cameraDistance;
        float zoomSpeed = 1.5f;
        float minCameraDistance = 10.0f; // Minimum zoom level
        float maxCameraDistance = 20.0f; // Maximum zoom level
        float smoothFactor = 0.1f;       // Adjust this for smoother or faster transitions

        // Get mouse wheel movement
        float mouseWheelMove = GetMouseWheelMove();

        // Update target camera distance based on mouse wheel input
        if (mouseWheelMove != 0)
        {
            targetCameraDistance -= mouseWheelMove * zoomSpeed;

            // Clamp the target camera distance to min and max values
            if (targetCameraDistance < minCameraDistance)
                targetCameraDistance = minCameraDistance;
            if (targetCameraDistance > maxCameraDistance)
                targetCameraDistance = maxCameraDistance;
        }

        // Smoothly interpolate the camera distance towards the target distance
        CharacterCamera::cameraDistance += (targetCameraDistance - CharacterCamera::cameraDistance) * smoothFactor;
    }

    static void UpdateCamera(Vector3 *characterPosition)
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

        rotationInput += (mouseDelta.x < 0) ? turningModifier : (mouseDelta.x > 0) ? -turningModifier
                                                                                   : 0;

        targetAngle += rotationInput;

        cameraRotationAngle += (targetAngle - cameraRotationAngle) * 0.1f;

        Vector3 forwardDirection = {
            sinf(DEG2RAD * cameraRotationAngle),
            0.0f,
            cosf(DEG2RAD * cameraRotationAngle)};

        float forwardLength = (forwardDirection.x * forwardDirection.x) + (forwardDirection.z * forwardDirection.z);
        forwardDirection.x /= forwardLength;
        forwardDirection.z /= forwardLength;

        camera.position.x = characterPosition->x + cameraDistance * forwardDirection.x;
        camera.position.z = characterPosition->z + cameraDistance * forwardDirection.z;
        camera.position.y = SurfaceManager::GetHeightAtPosition(camera.position.x, camera.position.z) + 3.5f; // Adjust height as necessary

        camera.target = *characterPosition;
    }

private:
    static float cameraDistance;
    constexpr static float turningModifier = 20.5f;
};

Camera CharacterCamera::camera = {0};
float CharacterCamera::cameraDistance = 15.0f;
float CharacterCamera::cameraRotationAngle = 0.0f;
