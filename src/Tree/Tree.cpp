#include "Tree/Tree.h"

Shader doubleSidedShader; // Declare a shader variable
void Tree::LoadTrees()
{
    treeModel = LoadModel("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Models/ac_tree_test/untitled.gltf");
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
        float x = static_cast<float>(std::rand() % 200 - 100);
        float z = static_cast<float>(std::rand() % 200 - 100);
        Vector3 newPos = {x, 0.0f, z};

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

    std::cout << "[LOADED]: Trees" << std::endl;
}

void Tree::UnloadTrees()
{
    UnloadModel(treeModel);
    UnloadShader(doubleSidedShader); // Unload the shader
    std::cout << "[UNLOADED]: Trees" << std::endl;
}

void Tree::DrawTrees()
{
    // Set the shader to be used for rendering the trees
    BeginShaderMode(doubleSidedShader);

    for (const auto &position : treePositions)
    {
        DrawModel(treeModel, position, 0.9f, WHITE);
    }

    // End shader mode
    EndShaderMode();
}
