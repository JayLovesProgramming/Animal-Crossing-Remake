// Map/Map.h
#pragma once


class SurfaceManager
{
public:
    static Model model;
    static Image noiseImage; // Store the noise image for continuous sampling

    const static auto GRID_SIZE = 20; // Too high values spread out the texture
    constexpr static auto GROUND_SIZE = (GRID_SIZE / 2);

    constexpr static auto TEXTURE_REPEAT = GRID_SIZE * 2.94; // Lower values spread the texture out

    constexpr static auto curveStrength = 0.0f; // Not doing a lot for now - Set to 0
    constexpr static auto noiseScale = 0.0f; // Not doing a lot for now - Set to 0
    
    constexpr static auto curvature = 0.002f;
    // Store the heights and noise values seperately
    static float heightMap[GRID_SIZE][GRID_SIZE];
    static float noiseMap[GRID_SIZE][GRID_SIZE];

    // Map Boundaries - TODO: Recalculate to get the proper boundaries
    constexpr static auto BOUNDARY_MIN_X = -((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MIN_Z = -((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MAX_X = ((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MAX_Z = ((GRID_SIZE / 2) * GROUND_SIZE);

    // Get interpolated noise value at any position
    static float GetNoiseAt(float x, float z);

    // Get the exact height at any world position
    static float GetHeightAtPosition(float x, float z);

    // Calculate the curved height
    static float CalculateCurvedHeight(float x, float z);

    static Vector3 GetSurfaceNormalAtPosition(float x, float z);

    static void GenerateGroundSurface();

    static void DrawGround();
    
    static void UnloadGround();

private:
};

Model SurfaceManager::model;
Image SurfaceManager::noiseImage;
float SurfaceManager::heightMap[GRID_SIZE][GRID_SIZE];
float SurfaceManager::noiseMap[GRID_SIZE][GRID_SIZE];
SurfaceManager grounds[SurfaceManager::GRID_SIZE][SurfaceManager::GRID_SIZE];
