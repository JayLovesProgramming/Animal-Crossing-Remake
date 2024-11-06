// Map/Tree/Tree.h
#pragma once

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include "Map/Ground/Ground.h"
#include <vector>
#include <iostream>

using std::cout, std::endl;

class Tree
{
public:
    inline static Model treeModel;
    inline static Shader doubleSidedShader;
    inline static std::vector<Vector3> treePositions;
    static constexpr auto treeCollisionRadius = 1.45f;
    static constexpr auto numberOfTrees = 300;
    static constexpr auto treeSpacing = 5.0f;
    static constexpr int xRange = 300;
    static constexpr int zRange = 300;

    static void LoadTrees();

    static void DrawTrees();

    static void UnloadTrees();
};

