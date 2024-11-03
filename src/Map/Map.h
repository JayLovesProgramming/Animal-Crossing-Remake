// Map/Map.h
#pragma once

#include "Debug/Debug.h"

#include "raylib.h"
#include "raymath.h"

#include <cmath>

const static auto MAP_SHADER_TYPE = 0;
const static auto GRID_SIZE = 20;
const static auto GROUND_SIZE = 10.0f;
const static auto BOUNDARY_MIN_X = -((GRID_SIZE / 2) * GROUND_SIZE);
const static auto BOUNDARY_MIN_Z = -((GRID_SIZE / 2) * GROUND_SIZE);
const static auto BOUNDARY_MAX_X = ((GRID_SIZE / 2) * GROUND_SIZE);
const static auto BOUNDARY_MAX_Z = ((GRID_SIZE / 2) * GROUND_SIZE);
const static auto TEXTURE_REPEAT = 10.0f;

class SurfaceManager
{
public:
    static Model model;

    static Image noiseImage; // Store the noise image for continuous sampling
    constexpr static auto curveStrength = 2.0f;
    constexpr static auto noiseScale = 0.5f;
    constexpr static auto curvature = 0.001f;
    // Store the heights and noise values seperately
     static float heightMap[GRID_SIZE][GRID_SIZE];
     static float noiseMap[GRID_SIZE][GRID_SIZE];

    // Get interpolated noise value at any position
    static float GetNoiseAt(float x, float z)
    {
        // Convert the world coords to grid coords
        float gridX = (x - BOUNDARY_MIN_X) / GROUND_SIZE;
        float gridZ = (z - BOUNDARY_MIN_Z) / GROUND_SIZE;

        // Get the int coords
        int x0 = (int)gridX;
        int z0 = (int)gridZ;

        x0 = Clamp(x0, 0, GRID_SIZE - 2);
        z0 = Clamp(z0, 0, GRID_SIZE - 2);

        int x1 = x0 + 1;
        int z1 = z0 + 1;

        // Get the fractional parts
        float fracX = gridX - x0;
        float fracZ = gridZ - z0;

        // Get the noise values at the four corners
        float n00 = noiseMap[x0][z0];
        float n01 = noiseMap[x0][z1];

        float n10 = noiseMap[x1][z0];
        float n11 = noiseMap[x1][x1];

        // Bilinear interpolation
        float nx0 = n00 * (1 - fracX) + n10 * fracX;
        float nx1 = n01 * (1 - fracX) + n11 * fracX;

        return nx0 * (1 - fracX) + nx1 * fracZ;
    }

    // Get the exact height at any world position
    static float GetHeightAtPosition(float x, float z)
    {
        // Calculate the base curved height
        float baseHeight = CalculateCurvedHeight(x, z);

        // Get the interpolated noise value
        float noiseValue = GetNoiseAt(x, z);

        // Combine base height with noise
        float returnValue = baseHeight + (noiseValue * curveStrength);
        return returnValue;
    }

    // Calculate the curved height
    static float CalculateCurvedHeight(float x, float z)
    {
        float centerX = 0;                                  // Init the center X coord for the curve
        float centerZ = 0;                                  // Init the center Z coord for the curve
        float dx = x - centerX;                             // Calculate the difference in the x-direction from the center
        float dz = z - centerZ;                             // Calculate the difference in the z-direction from the center
        float distanceFromCenter = sqrt(dx * dx + dz * dz); // Calculate the Euclidean distance from the center to the point (Distance formula: √(dx² + dz²))

        // Calculate the curved height based on the distance from the center and the curvature factor
        // The result is negated to imply that the height decreases as the distance increases
        return -(distanceFromCenter * distanceFromCenter) * curvature; // Curvature effect on height
    }

    static void GenerateGroundSurface(Texture2D grassTexture)
    {
        int vertexCount = GRID_SIZE * GRID_SIZE;
        int triangleCount = (GRID_SIZE - 1) * (GRID_SIZE - 1) * 2;

        float *vertices = (float *)MemAlloc(vertexCount * 3 * sizeof(float));
        float *texCoords = (float *)MemAlloc(vertexCount * 2 * sizeof(float));
        float *normals = (float *)MemAlloc(vertexCount * 3 * sizeof(float));
        unsigned short *indices = (unsigned short *)MemAlloc(triangleCount * 3 * sizeof(unsigned short));

        noiseImage = GenImagePerlinNoise(GRID_SIZE, GRID_SIZE, 0, 0, noiseScale);

        // Store noise values and generate vertices
        for (int z = 0; z < GRID_SIZE; z++)
        {
            for (int x = 0; x < GRID_SIZE; x++)
            {
                int vertex = (z * GRID_SIZE + x);

                float xPos = (x - GRID_SIZE / 2.0f) * GROUND_SIZE;
                float zPos = (z - GRID_SIZE / 2.0f) * GROUND_SIZE;

                // Store noise value
                Color color = GetImageColor(noiseImage, x, z);
                float noiseValue = (color.r / 255.0f) * 2.0f - 1.0f;
                noiseMap[x][z] = noiseValue;

                // Calculate the height using exact same method as GetHeightAtPosition
                float yPos = CalculateCurvedHeight(xPos, zPos) + (noiseValue * curveStrength);
                heightMap[x][z] = yPos;

                vertices[vertex * 3 + 0] = xPos;
                vertices[vertex * 3 + 1] = yPos;
                vertices[vertex * 3 + 2] = zPos;

                float u = (xPos / GROUND_SIZE) * (TEXTURE_REPEAT / GRID_SIZE);
                float v = (zPos / GROUND_SIZE) * (TEXTURE_REPEAT / GRID_SIZE);

                texCoords[vertex * 2 + 0] = u;
                texCoords[vertex * 2 + 1] = v;

                normals[vertex * 3 + 0] = 0.0f;
                normals[vertex * 3 + 1] = 1.0f;
                normals[vertex * 3 + 2] = 0.0f;
            }
        }
        // Generate indices
        int index = 0;
        for (int z = 0; z < GRID_SIZE - 1; z++)
        {
            for (int x = 0; x < GRID_SIZE - 1; x++)
            {
                unsigned short topLeft = (z * GRID_SIZE + x);
                unsigned short topRight = topLeft + 1;
                unsigned short bottomLeft = ((z + 1) * GRID_SIZE + x);
                unsigned short bottomRight = bottomLeft + 1;

                indices[index++] = topLeft;
                indices[index++] = bottomLeft;
                indices[index++] = topRight;

                indices[index++] = bottomLeft;
                indices[index++] = bottomRight;
                indices[index++] = topRight;
            }
        }

        Mesh mesh = {0};
        mesh.vertexCount = vertexCount;
        mesh.triangleCount = triangleCount;
        mesh.vertices = vertices;
        mesh.texcoords = texCoords;
        mesh.normals = normals;
        mesh.indices = indices;

        UploadMesh(&mesh, false);

        model = LoadModelFromMesh(mesh);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grassTexture;
        SetTextureWrap(model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture, TEXTURE_WRAP_REPEAT);
    };

    static void DrawGround()
    {
        if (WIRE_FLOOR)
        {
            DrawModelWires(model, Vector3{0, 0, 0}, 1.0f, WHITE);
        }
        else
        {
            DrawModel(model, Vector3{0, 0, 0}, 1.0f, WHITE);
        }
    };

    static void UnloadGround()
    {
        UnloadModel(model);
        UnloadImage(noiseImage);
        std::cout << "[UNLOADED]: Ground" << std::endl;
    }

private:
 
};

Model SurfaceManager::model;
Image SurfaceManager::noiseImage;
float SurfaceManager::heightMap[GRID_SIZE][GRID_SIZE];
float SurfaceManager::noiseMap[GRID_SIZE][GRID_SIZE];
SurfaceManager grounds[GRID_SIZE][GRID_SIZE];
