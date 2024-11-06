#include "Tree.h"
#include "Map/Ground/Ground.h"

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <iostream>
using std::cout, std::endl;

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
}

void Tree::UnloadTrees()
{
    UnloadModel(treeModel);
    UnloadShader(doubleSidedShader); // Unload the shader
    cout << "[UNLOADED]: " << numberOfTrees << " Trees" << endl;
}

void Tree::DrawTrees()
{
    // Set the shader to be used for rendering the trees
    BeginShaderMode(doubleSidedShader);

    for (const auto &position : treePositions)
    {
        // float mapRotation = Map::CalculateRotationForObject(position.x, position.z);
        // rlPushMatrix();
        DrawCylinder(position, treeCollisionRadius, treeCollisionRadius, 2, 0, LIME);
        // DrawSphere(position, treeCollisionRadius, PINK); // Visualize with a red sphere
        // rlRotatef(mapRotation * (180.0f / PI), -0.01f, 0.0f, 0.0f);
        DrawModel(treeModel, position, 0.9f, WHITE);
        // rlPopMatrix();
    }

    // End shader mode
    EndShaderMode();
}
