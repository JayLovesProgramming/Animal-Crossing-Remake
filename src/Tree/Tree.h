// Tree/Tree.h
#pragma once

#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <iostream>

class Tree
{
public:
    Model treeModel;
    std::vector<Vector3> treePositions;
    const float treeCollisionRadius = 1.45f;
    const int numberOfTrees = 1000;
    const float treeSpacing = 5.0f;

    Tree(); // Constructor declaration
    
    ~Tree(); // Destructor declaration

    void LoadTrees();

    void UnloadTrees();

    void DrawTrees();

};

Tree trees;
