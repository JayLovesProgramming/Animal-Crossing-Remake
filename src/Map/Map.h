// Map/Map.h
#pragma once

#include "Debug/Debug.h"
#include "raylib.h"

const static auto MAP_SHADER_TYPE = 0;
const static auto GRID_SIZE = 25;
const static auto GROUND_SIZE = 2.0f;
const static auto CURVE_AMPLITUDE = 15.0f;
const static auto CURVE_FREQUENCY = 0.5f;

const static auto BOUNDARY_MIN_X = -((GRID_SIZE / 2) * GROUND_SIZE);
const static auto BOUNDARY_MIN_Z = -((GRID_SIZE / 2) * GROUND_SIZE);
const static auto BOUNDARY_MAX_X = ((GRID_SIZE / 2) * GROUND_SIZE);
const static auto BOUNDARY_MAX_Z = ((GRID_SIZE / 2) * GROUND_SIZE);

class SurfaceManager
{
public:
    Model model;
    Vector3 positions[GRID_SIZE][GRID_SIZE];
    
    void GenerateGroundSurface(Texture2D grassTexture)
    {
        Mesh baseMesh = GenMeshPlane(GROUND_SIZE, GROUND_SIZE, 10, 10);

        model = LoadModelFromMesh(baseMesh);
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grassTexture;

        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int z = 0; z < GRID_SIZE; z++)
            {
                float xOffset = (x - GRID_SIZE / 2) * GROUND_SIZE;
                float zOffset = (z - GRID_SIZE / 2) * GROUND_SIZE;
                positions[x][z] = Vector3{xOffset, 0.0f, zOffset};
            }
        }
    }

    void DrawGround()
    {
        // Gets the info for the ground/surface and draws it on the screen
        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int z = 0; z < GRID_SIZE; z++)
            {
                if (WIRE_FLOOR)
                {
                    DrawModelWires(model, positions[x][z], 1.0f, WHITE);
                }
                else
                {
                    DrawModel(model, positions[x][z], 1.0f, WHITE);
                }
            }
        }
    }
};

SurfaceManager surfaceManager;
