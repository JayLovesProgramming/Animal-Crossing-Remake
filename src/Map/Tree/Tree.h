// Map/Tree/Tree.h
#pragma once

#include <vector>

class Tree
{
public:
    inline static Model treeModel;
    inline static Shader doubleSidedShader;
    inline static std::vector<Vector3> treePositions;
    static constexpr auto treeCollisionRadius = 1;
    static constexpr auto numberOfTrees = 300;
    static constexpr auto treeSpacing = 5.0f;
    static constexpr int xRange = 300;
    static constexpr int zRange = 300;
    inline static float treeHeightThreshold = 50.0f;

    static void LoadTrees();

    static void DrawTrees();

    static void UnloadTrees();
};

