// Ground/Ground.h
#pragma once

using std::string;

class Map
{
public:
    inline static Model model;
    inline static Image noiseImage; // Store the noise image for continuous sampling

    const static auto GRID_SIZE = 90; // Too high values spread out the texture
    constexpr static auto GROUND_SIZE = (GRID_SIZE / 2);

    constexpr static auto TEXTURE_REPEAT = GRID_SIZE * 3.5f; // Lower values spread the texture out

    constexpr static auto curveStrength = 0.0f; // Not doing a lot for now - Set to 0
    constexpr static auto noiseScale = 0.0f; // Not doing a lot for now - Set to 0
    
    constexpr static auto curvature = 0.00f;
    // Store the heights and noise values seperately
    inline static float heightMap[GRID_SIZE][GRID_SIZE];
    inline static float noiseMap[GRID_SIZE][GRID_SIZE];

    inline static Vector3 riverLocation {-25.0f, 0.0f, -32.5f};

    // Map Boundaries - TODO: Recalculate to get the proper boundaries
    constexpr static auto BOUNDARY_MIN_X = -((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MIN_Z = -((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MAX_X = ((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MAX_Z = ((GRID_SIZE / 2) * GROUND_SIZE);

    // Get interpolated noise value at any position
    inline static float GetNoiseAt(float x, float z);

    // Get the exact height at any world position
    inline static float GetHeightAtPosition(float x, float z, string type);

    // Calculate the curved height
    inline static float CalculateCurvedHeight(float x, float z);

    inline static Vector3 GetSurfaceNormalAtPosition(float x, float z);

    inline static void GenerateGroundSurface();

    inline static void DrawGround();
    
    inline static void UnloadGround();

private:
};

