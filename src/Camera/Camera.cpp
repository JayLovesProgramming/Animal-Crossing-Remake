// Camera/Camera.cpp
#include "Camera/Camera.h"

void CharacterCamera::InitCamera()
{
    camera.position = Vector3{0.0f, 0.0f, 0.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 35.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    lastNormal = {0.0f, 1.0f, 0.0f}; // Initialize last normal
};

void CharacterCamera::UpdateCameraModeProjection()
{
    if (IsKeyReleased(KEY_F5))
    {
        camera.projection = (camera.projection == CAMERA_ORTHOGRAPHIC) ? CAMERA_PERSPECTIVE : CAMERA_ORTHOGRAPHIC;
    }
};

void CharacterCamera::UpdateCameraZoom()
{
    static float targetCameraDistance = cameraDistance;
    const float zoomSpeed = 1.5f;
    const float minCameraDistance = 10.0f;
    const float maxCameraDistance = 20.0f;
    const float smoothFactor = 0.1f;

    float mouseWheelMove = GetMouseWheelMove();
    if (mouseWheelMove != 0)
    {
        targetCameraDistance -= mouseWheelMove * zoomSpeed;
        targetCameraDistance = Clamp(targetCameraDistance, minCameraDistance, maxCameraDistance);
    }

    cameraDistance = Lerp(cameraDistance, targetCameraDistance, smoothFactor);
};

Vector3 CharacterCamera::SmoothVector3(Vector3 current, Vector3 target, float smoothFactor)
{
    return {
        Lerp(current.x, target.x, smoothFactor),
        Lerp(current.y, target.y, smoothFactor),
        Lerp(current.z, target.z, smoothFactor)};
};

void CharacterCamera::UpdateCamera(Vector3 *characterPosition)
{
    UpdateCameraZoom();
    UpdateCameraModeProjection();

    // Handle rotation
    float targetAngle = cameraRotationAngle;
    Vector2 mouseDelta = GetMouseDelta();
    float rotationInput = 0.0f;

    rotationInput += (mouseDelta.x != 0) ? -mouseDelta.x * turningModifier * 0.01f : 0;

    targetAngle += rotationInput;
    cameraRotationAngle = Lerp(cameraRotationAngle, targetAngle, 0.1f);

    // Calculate base camera position relative to character
    float angleRad = DEG2RAD * cameraRotationAngle;
    Vector3 cameraOffset = {
        sinf(angleRad) * cameraDistance,
        0.0f,
        cosf(angleRad) * cameraDistance};

    // Calculate camera position on curved surface
    Vector3 rawCameraPos = {
        characterPosition->x + cameraOffset.x,
        0.0f,
        characterPosition->z + cameraOffset.z};

    // Get heights
    float characterGroundHeight = SurfaceManager::GetHeightAtPosition(characterPosition->x, characterPosition->z);
    float cameraGroundHeight = SurfaceManager::GetHeightAtPosition(rawCameraPos.x, rawCameraPos.z);

    // characterGroundHeight = 0.0f; // This locks to the character
    // std::cout << "[CHARACTER] Ground Height: " << characterGroundHeight << std::endl;


    // Get and smooth surface normal
    Vector3 currentNormal = SurfaceManager::GetSurfaceNormalAtPosition(rawCameraPos.x, rawCameraPos.z);
    Vector3 smoothedNormal = SmoothVector3(lastNormal, currentNormal, 0.05f); // Reduced smoothing factor
    lastNormal = smoothedNormal;

    // Normalize the smoothed normal
    float length = sqrtf(smoothedNormal.x * smoothedNormal.x +
                         smoothedNormal.y * smoothedNormal.y +
                         smoothedNormal.z * smoothedNormal.z);
    smoothedNormal.x /= length;
    smoothedNormal.y /= length;
    smoothedNormal.z /= length;

    // Calculate camera height while maintaining constant distance from surface
    const float heightOffset = 3.5f;
    Vector3 heightVector = Vector3Scale(smoothedNormal, heightOffset);

    // Set final camera position with averaged height
    static float lastCameraHeight = cameraGroundHeight;
    float targetHeight = cameraGroundHeight + heightVector.y;
    lastCameraHeight = Lerp(lastCameraHeight, targetHeight, 0.1f);

    camera.position = {
        rawCameraPos.x,
        lastCameraHeight,
        rawCameraPos.z};

    // Set smoothed up vector
    camera.up = smoothedNormal;

    // Set target position with smoothed height
    camera.target = *characterPosition;
    static float lastTargetHeight = characterGroundHeight;
    float targetHeightOffset = 1.0f;
    float newTargetHeight = characterGroundHeight + targetHeightOffset;
    lastTargetHeight = Lerp(lastTargetHeight, newTargetHeight, 0.1f);
    camera.target.y = lastTargetHeight;
};
