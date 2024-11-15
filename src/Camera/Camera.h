// Camera/Camera.h
#pragma once

#include "Utils/Utils.h"

using std::cout, std::endl;

class CharacterCamera {
public:
    inline static Camera camera = { 0 };
    inline static float cameraRotationAngle  = 0.0f;
    inline static Vector3 lastNormal = {0.0f, 1.0f, 0.0f};  // Store last normal for smoothing

    static void InitalizeCamera();

    static Vector3 SmoothVector3(Vector3 current, Vector3 target, float smoothFactor);

    static void UpdateCamera(Vector3* characterPos);

private:
    constexpr static float turningModifier = 20.5f;
};
