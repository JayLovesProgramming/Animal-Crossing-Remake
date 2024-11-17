#include "CameraZoom.h"
#include "raylib.h"
#include "raymath.h"

void CameraZoom::UpdateCameraZoom()
{
    static float targetCameraDistance = cameraDistance;
    const float zoomSpeed = 1.5f;
    const float minCameraDistance = 7.0f;
    const float maxCameraDistance = 10.0f;
    const float smoothFactor = 0.2f;

    float mouseWheelMove = GetMouseWheelMove();
    if (mouseWheelMove != 0)
    {
        targetCameraDistance -= mouseWheelMove * zoomSpeed;
        targetCameraDistance = Clamp(targetCameraDistance, minCameraDistance, maxCameraDistance);
    }

    cameraDistance = Lerp(cameraDistance, targetCameraDistance, smoothFactor);
};
