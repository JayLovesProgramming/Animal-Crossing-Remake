// Tree/Tree.h
#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>

class Tree
{
public:
    inline static Model treeModel;
    inline static std::vector<Vector3> treePositions;
    static constexpr auto treeCollisionRadius = 1.45f;
    static constexpr auto numberOfTrees = 50;
    static constexpr auto treeSpacing = 5.0f;

    static void LoadTrees();

    static void DrawTrees();

    static void UnloadTrees();
};

