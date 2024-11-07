// Map/Tree/Tree.h
#pragma once

#include <vector>

class Tree
{
public:
    inline static Model treeModel;
    inline static Shader doubleSidedShader;
    inline static std::vector<Vector3> treePositions;
    static constexpr auto treeCollisionRadius = 1.5f;
    static constexpr auto numberOfTrees = 555;
    static constexpr auto treeSpacing = 5.0f;
    static constexpr int xRange = 150;
    static constexpr int zRange = 150;
    inline static float treeHeightThreshold = 50.0f;

    inline static float rotX;

    static void RotateTrees(Vector3 position);

    static void LoadTrees();

    static void DrawTrees();

    static void BeginTreeShader();
    static void EndTreeShader();

    static void UnloadTrees();
};

