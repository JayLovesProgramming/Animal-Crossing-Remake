#pragma once

#include "Map/Map.h"

class CharacterCamera {
public:
    static Camera camera;
    static float cameraRotationAngle;
    static Vector3 lastNormal;  // Store last normal for smoothing

    static void InitCamera();

    static void UpdateCameraModeProjection();

    static void UpdateCameraZoom();

    static Vector3 SmoothVector3(Vector3 current, Vector3 target, float smoothFactor);

    static void UpdateCamera(Vector3* characterPosition);

private:
    static float cameraDistance;
    constexpr static float turningModifier = 20.5f;

    static float Lerp(float start, float end, float amount) {
        return start + amount * (end - start);
    }

    static float Clamp(float value, float min, float max) {
        return (value < min) ? min : (value > max) ? max : value;
    }

    static Vector3 Vector3Scale(Vector3 v, float scale) {
        return { v.x * scale, v.y * scale, v.z * scale };
    }
};

// Static member initialization
Camera CharacterCamera::camera = {0};
float CharacterCamera::cameraDistance = 15.0f;
float CharacterCamera::cameraRotationAngle = 0.0f;
Vector3 CharacterCamera::lastNormal = {0.0f, 1.0f, 0.0f};
