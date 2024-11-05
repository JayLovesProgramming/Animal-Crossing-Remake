#include "Tree.h"


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

    std::srand(static_cast<unsigned int>(std::time(0)));
    treePositions.clear();

    while (treePositions.size() < numberOfTrees)
    {
        float x = static_cast<float>(std::rand() % xRange - zRange);
        float z = static_cast<float>(std::rand() % xRange - zRange);
        Vector3 newPos = {x, Map::GetHeightAtPosition(x, z), z};


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

    std::cout << "[LOADED]: " << numberOfTrees << " Trees" << std::endl;
}

void Tree::UnloadTrees()
{
    UnloadModel(treeModel);
    UnloadShader(doubleSidedShader); // Unload the shader
    std::cout << "[UNLOADED]: " << numberOfTrees << " Trees" << std::endl;
}

void Tree::DrawTrees()
{
    // Set the shader to be used for rendering the trees
    BeginShaderMode(doubleSidedShader);

    for (const auto &position : treePositions)
    {
        // float mapRotation = Map::CalculateRotationForObject(position.x, position.z);
        // rlPushMatrix();
        // rlRotatef(mapRotation * (180.0f / PI), -0.01f, 0.0f, 0.0f); 
        DrawModel(treeModel, position, 0.9f, WHITE);
        // rlPopMatrix();
    }

    // End shader mode
    EndShaderMode();
}
