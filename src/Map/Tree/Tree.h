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
    inline static float treeHeightThreshold = 50.0f;
    static constexpr auto numberOfTrees = 555;
    static constexpr auto treeSpacing = 3.0f;
    static constexpr int xRange = 550;
    static constexpr int zRange = 550;

    inline static float rotX;

    static void RotateTrees(Vector3 position);

    static void LoadTrees();

    static void DrawTrees();

    static void BeginTreeShader();
    static void EndTreeShader();

    static void UnloadTrees();

    static void HandleTreeCollision();
};

