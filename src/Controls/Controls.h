// Controls/Controls.h
#pragma once

class GameControls
{
public:
    inline static bool nearTree;
    inline static bool nearFlower;
    inline static Vector3 newPosition;
    inline static Vector3 initialPosition;

    // Initialize static variables
    inline static bool isJumping = false;
    inline static float verticalVelocity = 0.0f;
    inline static  float gravity = 18.0f;
    inline static  float jumpForce = 5.0f;

    static void UpdateControls(Vector3 *characterPos, float &characterSpeed);

    static void HandleNearbyObjectCollisions();

private:
    inline static int animFrameCounter = 0;
};
