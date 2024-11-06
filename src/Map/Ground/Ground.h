// Map/Map.h
#pragma once

#include <iostream> // TEMP TO DISABLE RED SQUIGGLY LINES
#include <stdio.h> // TEMP TO DISABLE RED SQUIGGLY LINES
#include "raymath.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "raylib.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Grass/Grass.h"
#include "Debug/Debug.h"

using std::string, std::cout, std::endl;

class Map
{
public:
    inline static Model model;
    inline static Image noiseImage; // Store the noise image for continuous sampling

    const static auto GRID_SIZE = 20; // Too high values spread out the texture
    constexpr static auto GROUND_SIZE = (GRID_SIZE / 2);

    constexpr static auto TEXTURE_REPEAT = GRID_SIZE * 2.94; // Lower values spread the texture out

    constexpr static auto curveStrength = 0.0f; // Not doing a lot for now - Set to 0
    constexpr static auto noiseScale = 0.0f; // Not doing a lot for now - Set to 0
    
    constexpr static auto curvature = 0.0025f;
    // Store the heights and noise values seperately
    inline static float heightMap[GRID_SIZE][GRID_SIZE];
    inline static float noiseMap[GRID_SIZE][GRID_SIZE];

    // Map Boundaries - TODO: Recalculate to get the proper boundaries
    constexpr static auto BOUNDARY_MIN_X = -((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MIN_Z = -((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MAX_X = ((GRID_SIZE / 2) * GROUND_SIZE);
    constexpr static auto BOUNDARY_MAX_Z = ((GRID_SIZE / 2) * GROUND_SIZE);

    // Get interpolated noise value at any position
    static float GetNoiseAt(float x, float z);

    // Get the exact height at any world position
    static float GetHeightAtPosition(float x, float z, string type);

    static float CalculateRotationForObject(float x, float z);

    // Calculate the curved height
    static float CalculateCurvedHeight(float x, float z);

    static Vector3 GetSurfaceNormalAtPosition(float x, float z);

    static void GenerateGroundSurface();

    static void DrawGround();
    
    static void UnloadGround();

private:
};

