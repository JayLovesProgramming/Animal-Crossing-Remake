// Tree/Tree.cpp
#include "Tree/Tree.h"

Tree::Tree() {
    // std::cout << "INIT TREE" << std::endl;
    // LoadTrees();
}

Tree::~Tree() {
    UnloadTrees();
}

void Tree::LoadTrees() {
    treeModel = LoadModel("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Models/coconut_tree/scene.gltf");
    for (int i = 0; i < treeModel.materialCount; i++) {
        SetTextureFilter(treeModel.materials[i].maps[MATERIAL_MAP_ALBEDO].texture, TEXTURE_FILTER_ANISOTROPIC_16X);
    }

    std::srand(static_cast<unsigned int>(std::time(0)));
    treePositions.clear();

    while (treePositions.size() < numberOfTrees) {
        float x = static_cast<float>(std::rand() % 200 - 100);
        float z = static_cast<float>(std::rand() % 200 - 100);
        Vector3 newPos = {x, 0.0f, z};

        bool isTreeSpaced = true;
        for (const Vector3& pos : treePositions) {
            float distance = Vector3Distance(newPos, pos);
            if (distance < treeSpacing) {
                isTreeSpaced = false;
                break;
            }
        }

        if (isTreeSpaced) {
            treePositions.push_back(newPos);
        }
    }

    std::cout << "Loaded trees" << std::endl;
}

void Tree::UnloadTrees() {
    UnloadModel(treeModel);
    std::cout << "Destroyed Tree Models" << std::endl;
}

void Tree::DrawTrees() {
    for (const Vector3 &treePos : treePositions) {
        DrawModel(treeModel, treePos, 0.9f, WHITE);
    }
}
