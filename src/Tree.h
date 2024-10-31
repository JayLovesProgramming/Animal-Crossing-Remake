#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>

class Tree
{
public:
    Model treeModel;
    std::vector<Vector3> treePositions;
    const float treeCollisionRadius = 1.45f;
    const int numberOfTrees = 200;
    const float treeSpacing = 5.0f;

    void LoadTrees()
    {
        treeModel = LoadModel("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Models/coconut_tree/scene.gltf"); // ! This should spawn
        // TODO: Let's attempt to do all scaling, rotation and positioning in Blender before we import the models
        for (int i = 0; i < treeModel.materialCount; i++)
        {
            SetTextureFilter(treeModel.materials[i].maps[MATERIAL_MAP_ALBEDO].texture, TEXTURE_FILTER_ANISOTROPIC_16X); // TEXTURE_FILTER_ANISOTROPIC_16X
        }

        std::srand(static_cast<unsigned int>(std::time(0))); // Seed for randomness
        treePositions.clear();

         while (treePositions.size() < numberOfTrees)
        {
            float x = static_cast<float>(std::rand() % 200 - 100); // Random X between -100 and 100
            float z = static_cast<float>(std::rand() % 200 - 100); // Random Z between -100 and 100
            Vector3 newPos = {x, 0.0f, z};

            // Check if the new position is far enough from existing positions
            bool isFarEnough = true;
            for (const Vector3& pos : treePositions)
            {
                float distance = Vector3Distance(newPos, pos);
                if (distance < treeSpacing)
                {
                    isFarEnough = false;
                    break;
                }
            }

            // If far enough, add to positions
            if (isFarEnough)
            {
                treePositions.push_back(newPos);
            }
        }

        std::cout << "Loaded trees" << std::endl;
    }

    void UnloadTrees()
    {
        UnloadModel(treeModel);
    }

    void DrawTrees()
    {
        // std::cout << "Drawing trees" << std::endl;
        for (const Vector3 &treePos : treePositions)
        {
            DrawModel(treeModel, treePos, 0.9f, WHITE);
        }
    }

private:
};

Tree trees;
