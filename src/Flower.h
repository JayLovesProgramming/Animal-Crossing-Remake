// Flower.h
#pragma once

#include "raylib.h"
#include "Debug.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cassert>

class Flower
{
public:
    Vector3 position;
    Color color = WHITE;
    float scale = 0.015f;
    static Model flowerModel;
    static std::vector<Flower> flowers;

    static void LoadFlowers()
    {
        if (DEBUG_FLOWERS)
        {
            std::cout << "Loaded flowers" << std::endl;
        }
        srand(static_cast<unsigned>(time(0)));
        flowerModel = LoadModel("../src/Assets/Models/plant/scene.gltf");
        assert(flowerModel.meshCount != 0);
        GenerateRandomFlowers(25, 50.0f, 50.0f);
    }

    static void DrawFlowers()
    {
        if (DEBUG_FLOWERS)
        {
            // std::cout << "Drawing flowers" << std::endl;
        }
        for (const Flower &flower : flowers)
        {
            DrawModel(flowerModel, flower.position, flower.scale, flower.color);
        }
    }

    static void GenerateRandomFlowers(int count, float xRange, float zRange)
    {
        for (int i = 0; i < count; ++i)
        {
            Flower flower;
            flower.position = {
                static_cast<float>(rand()) / RAND_MAX * xRange - (xRange / 2),
                0.0f,
                static_cast<float>(rand()) / RAND_MAX * zRange - (zRange / 2)
            };
            flower.color = GenerateRandomFlowerColour();
            flowers.push_back(flower);
        }
    }

    ~Flower()
    {
        if (DEBUG_FLOWERS)
        {
            std::cout << "DESTRUCTOR!!! FLOWER" << std::endl;
        }
        // UnloadModel(flowerModel);
    }

private:
    static Color GenerateRandomFlowerColour()
    {
        Color colors[] = {
            YELLOW,
            PINK,
        };
        return colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
    }
};

std::vector<Flower> Flower::flowers;
Model Flower::flowerModel;
