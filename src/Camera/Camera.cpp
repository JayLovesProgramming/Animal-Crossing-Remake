// Camera/Camera.cpp
#include "Camera.h"

#include "Controls/Controls.h"
#include "Map/Ground/Ground.h"
#include "raylib.h"
#include "raymath.h"
#include <cmath> 
#include <iostream>
#include "CameraZoom.h"

void CharacterCamera::InitalizeCamera()
{
    camera.position = Vector3{0.0f, 0.0f, 0.0f};
    camera.target = Vector3{0.0f, 0.0f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 55.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    lastNormal = {0.0f, 1.0f, 0.0f}; // Initialize last normal
};

Vector3 CharacterCamera::SmoothVector3(Vector3 current, Vector3 target, float smoothFactor)
{
    return {
        Lerp(current.x, target.x, smoothFactor),
        Lerp(current.y, target.y, smoothFactor),
        Lerp(current.z, target.z, smoothFactor)};
};

void CharacterCamera::UpdateCamera(Vector3 *characterPos)
{
    CameraZoom::UpdateCameraZoom();
    GameControls::HandleCameraPerspective();

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
        sinf(angleRad) * CameraZoom::cameraDistance,
        0.0f,
        cosf(angleRad) * CameraZoom::cameraDistance};

    // Calculate camera position on curved surface
    Vector3 rawCameraPos = {
        characterPos->x + cameraOffset.x,
        0.0f,
        characterPos->z + cameraOffset.z};

    // Get heights
    float characterGroundHeight = Map::GetHeightAtPosition(characterPos->x, characterPos->z, "camera");
    float cameraGroundHeight = Map::GetHeightAtPosition(rawCameraPos.x, rawCameraPos.z, "camera");

    // characterGroundHeight = 0.0f; // This locks to the character
    // cout << "[CHARACTER] Ground Height: " << characterGroundHeight << endl;


    // Get and smooth surface normal
    Vector3 currentNormal = Map::GetSurfaceNormalAtPosition(rawCameraPos.x, rawCameraPos.z);
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
    camera.target = *characterPos;
    static float lastTargetHeight = characterGroundHeight;
    float targetHeightOffset = 1.0f;
    float newTargetHeight = characterGroundHeight + targetHeightOffset;
    lastTargetHeight = Lerp(lastTargetHeight, newTargetHeight, 0.1f);
    camera.target.y = lastTargetHeight;
};
