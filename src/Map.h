#pragma once

const static auto MAP_SHADER_TYPE = 0; // Can also use MATERIAL_MAP_DIFFUSE from Raylib which == 0
const static auto GRID_SIZE = 20;
const static auto GROUND_SIZE = 5.0f;
const static auto CURVE_AMPLITUDE = 15.0f;
const static auto CURVE_FREQUENCY = 0.5f;

struct GroundTile
{
    Model model;
    Vector3 position;
};

// Generates a curved surface ? Randomized?
void GenerateCurvedGround(GroundTile grounds[GRID_SIZE][GRID_SIZE], Texture2D grassTexture)
{
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int z = 0; z < GRID_SIZE; z++)
        {
            float xOffset = (x - GRID_SIZE / 2) * GROUND_SIZE;
            float zOffset = (z - GRID_SIZE / 2) * GROUND_SIZE;

            Mesh mesh = GenMeshPlane(GROUND_SIZE, GROUND_SIZE, 10, 10);
            for (int i = 0; i < mesh.vertexCount; i++)
            {
                Vector3 *vertex = (Vector3 *)&mesh.vertices[i * 3];
                float height = CURVE_AMPLITUDE * sinf(CURVE_FREQUENCY * (vertex->x + xOffset + vertex->z + zOffset));
                vertex->y = height;
                // float xPosition = vertex->x + xOffset;
                // float zPosition = vertex->y + zOffset;
                // vertex->y += CURVE_AMPLITUDE * sinf(CURVE_FREQUENCY * (xPosition, zPosition));
            }

            grounds[x][z].model = LoadModelFromMesh(mesh);
            grounds[x][z].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grassTexture;
            grounds[x][z].position = Vector3{xOffset, 0.0f, zOffset};
        }
    }
};
