// Camera/Camera.h
#pragma once

using std::cout, std::endl;

class CharacterCamera {
public:
    inline static Camera camera = { 0 };
    inline static float cameraRotationAngle  = 0.0f;
    inline static Vector3 lastNormal = {0.0f, 1.0f, 0.0f};  // Store last normal for smoothing

    static void InitCamera();

    static void UpdateCameraModeProjection();

    static Vector3 SmoothVector3(Vector3 current, Vector3 target, float smoothFactor);

    static void UpdateCamera(Vector3* characterPos);

private:
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
