#include "Tree.h"
#include "Map/Ground/Ground.h"
#include "Character/Character.h"

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>
using std::cout, std::endl;

// TODO: Implement a feature so the trees have a bounding box so we can use that. Sort of doing it a cheap way currently

void Tree::LoadTrees()
{
    treeModel = LoadModel("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Models/treetest/treetest.gltf");
    for (int i = 0; i < treeModel.materialCount; i++)
    {
        SetTextureFilter(treeModel.materials[i].maps[MATERIAL_MAP_ALBEDO].texture, TEXTURE_FILTER_ANISOTROPIC_16X);
    }

    // Load the double-sided shader
    doubleSidedShader = LoadShader(0, "C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Shaders/Fragment Shaders/double_sided.fs");

    // Set up the shader uniforms
    Vector3 lightPos = {10.0f, 10.0f, 10.0f};
    SetShaderValue(doubleSidedShader, GetShaderLocation(doubleSidedShader, "lightPosition"), &lightPos, SHADER_UNIFORM_VEC3);
    Vector4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
    SetShaderValue(doubleSidedShader, GetShaderLocation(doubleSidedShader, "lightColor"), &lightColor, SHADER_UNIFORM_VEC4);

    srand(static_cast<unsigned int>(time(0)));
    treePositions.clear();

    while (treePositions.size() < numberOfTrees)
    {
        float x = static_cast<float>(rand() % xRange - zRange);
        float z = static_cast<float>(rand() % xRange - zRange);
        Vector3 newPos = {x, Map::GetHeightAtPosition(x, z, "tree"), z};

        bool isTreeSpaced = true;
        for (const Vector3 &pos : treePositions)
        {
            float distance = Vector3Distance(newPos, pos);
            if (distance < treeSpacing)
            {
                isTreeSpaced = false;
                break;
            }
        }

        if (isTreeSpaced)
        {
            treePositions.push_back(newPos);
        }
    }

    cout << "[LOADED]: " << numberOfTrees << " Trees" << endl;
};

void Tree::UnloadTrees()
{
    UnloadModel(treeModel);
    UnloadShader(doubleSidedShader); // Unload the shader
    cout << "[UNLOADED]: " << numberOfTrees << " Trees" << endl;
};

void Tree::BeginTreeShader()
{
    BeginShaderMode(doubleSidedShader);
    // Intend to implment some other shit here later down the line
};

void Tree::EndTreeShader()
{
    rlPopMatrix();
    EndShaderMode();
    // Intend to implment some other shit here later down the line
};

void Tree::RotateTrees(Vector3 position)
{
    float mapCurvature = Map::curvature;
    // float mapRotation = mapCurvature * (180.0f / PI);
    // float mapRotation = 15.0f;

    Vector3 normal = Map::GetSurfaceNormalAtPosition(position.x, position.z);

    rotX = atan2f(normal.z, normal.y) * (180.0f / PI);
    float rotZ = atan2f(normal.x, normal.y) * (180.0f / PI);


    rlPushMatrix();

    // rlRotatef(rotX, 1.0f, 0.0f, 0.0f);
    rlRotatef(rotX, 0.0f, 0.0f, 0.0f); // Calc the maps curvature??
    // rlRotatef(rotZ, 0.0f, 0.0f, -1.0f);
    
};

void Tree::DrawTrees()
{
    for (const auto &position : treePositions)
    {

        RotateTrees(position);
        // DrawSphere(position, treeCollisionRadius, PINK); // Visualize with a red sphere
        // DrawSphere(position, treeCollisionRadius, Color{255, 20, 147, 250}); // PINK with 50% opacity - useful for debugging rlEnableBackfaceCulling

        BeginTreeShader();

        DrawModel(treeModel, position, 0.9f, WHITE);

        EndTreeShader();
    }
};
