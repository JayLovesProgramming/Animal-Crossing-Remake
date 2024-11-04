// Flower/Flower.h
#pragma once

#include "raylib.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include "Map/Ground/Ground.h" // TEMP TO DISABLE RED SQUIGGLY LINES
#include <iostream> // TEMP TO DISABLE RED SQUIGGLY LINES
#include <vector> // TEMP TO DISABLE RED SQUIGGLY LINES
#include <cassert> // TEMP TO DISABLE RED SQUIGGLY LINES
#include <cstdlib> // TEMP TO DISABLE RED SQUIGGLY LINES
#include <ctime> // TEMP TO DISABLE RED SQUIGGLY LINES

class Flower
{
public:
    Vector3 position;
    Color color = WHITE;
    float scale = 0.018f;
    inline static Model flowerModel;
    inline static std::vector<Flower> flowers;
    const static int numberOfFlowers = 1500;
    inline const static auto xRange = 300.0f;
    inline const static auto zRange = 300.0f;

    static void LoadFlowers();

    static void DrawFlowers();

    static void GenerateRandomFlowers(int count);

    static void UnloadFlowers();

private:
    static Color GenerateRandomFlowerColour();
};
