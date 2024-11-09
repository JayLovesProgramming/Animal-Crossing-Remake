// Flower/Flower.cpp
#include "Flower.h"

#include "raylib.h"
#include "Map/Ground/Ground.h"
#include "Controls/Controls.h"
#include "Utils/ConsoleOut.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>

using std::cout, std::endl;

void Flower::LoadFlowers()
{
    if (numberOfFlowers > 0)
    {
        srand(static_cast<unsigned>(time(0)));
        flowerModel = LoadModel("../src/Assets/Models/plant/scene.gltf");
        assert(flowerModel.meshCount > 0);
        GenerateRandomFlowers(numberOfFlowers);
        cout << "[LOADED]: " << numberOfFlowers << " Flowers" << endl;
    }
};

void Flower::HandleFlowerCollision()
{
    // Iterate through each flower to check for collisions
    for (const auto &flower : flowers)
    {
        // Calculate horizontal distance (ignore y-axis)
        float horizontalDistance = sqrtf(
            (GameControls::newPosition.x - flower.position.x) * (GameControls::newPosition.x - flower.position.x) +
            (GameControls::newPosition.z - flower.position.z) * (GameControls::newPosition.z - flower.position.z));

        // Calculate vertical distance (y-axis)
        float verticalDistance = fabs(GameControls::newPosition.y - flower.position.y);

        // If within both horizontal and vertical distance thresholds, consider it a collision
        if (horizontalDistance <= flowerCollisionRadius && verticalDistance <= flowerHeightThreshold)
        {
            GameControls::nearFlower = true;
            break;
        }
        GameControls::nearFlower = false;
    }
}

void Flower::DrawFlowers()
{
    if (numberOfFlowers > 0)
    {
        for (const Flower &flower : flowers)
        {
            DrawModel(flowerModel, flower.position, flower.scale, WHITE);
        }
    }
};

void Flower::GenerateRandomFlowers(int count)
{
    Flower flower;
    for (int i = 0; i < count; ++i)
    {
        float flowerX = static_cast<float>(rand()) / RAND_MAX * xRange - (xRange / 2);
        float flowerZ = static_cast<float>(rand()) / RAND_MAX * zRange - (zRange / 2);
        flower.position = {
            flowerX,
            Map::GetHeightAtPosition(flowerX, flowerZ, "flower"),
            flowerZ};
        flower.color = GenerateRandomFlowerColour();
        flowers.push_back(flower);
    }
};

void Flower::UnloadFlowers()
{
    UnloadModel(flowerModel);
    cout << unloadString << numberOfFlowers << "Flowers" << endl;
};

Color Flower::GenerateRandomFlowerColour()
{
    Color colours[] = {
        YELLOW,
        PINK,
    };
    return colours[rand() % (sizeof(colours) / sizeof(colours[0]))];
};
