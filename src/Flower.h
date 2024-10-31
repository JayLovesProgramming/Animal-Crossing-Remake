// Flower.h
#pragma once

#include "raylib.h"
#include "Debug.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Flower
{
public:
    Vector3 position;
    Color color = WHITE;
    float scale = 0.015f;
    Model flowerModel;
    static std::vector<Flower> flowers;

    void LoadFLowers()
    {
        if (DEBUG_FLOWERS)
        {
            std::cout << "Loaded flowers" << std::endl;
        }
        srand(static_cast<unsigned>(time(0)));
        flowerModel = LoadModel("../src/Assets/Models/plant/scene.gltf");
        assert(flowerModel.meshCount != 0);
        // Shader defaultShader = LoadShader(NULL, NULL);
        // flowerModel.materials[0].shader = defaultShader;
    }
    void DrawFlowerS()
    {
        if (DEBUG_FLOWERS)
        {
            std::cout << "Drawing flowers" << std::endl;
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
                static_cast<float>(rand()) / RAND_MAX * xRange - (xRange / 2), // Random X in range [-xRange/2, xRange/2]
                0.0f,
                static_cast<float>(rand()) / RAND_MAX * zRange - (zRange / 2) // Random Z in range [-zRange/2, zRange/2]
            };
            flower.color = GenerateRandomFlowerColour();
            flowers.push_back(flower);
        }
    }

private:
    static Color GenerateRandomFlowerColour()
    {
        Color colors[] = {
            YELLOW, // Good
            PINK,   // Dont really like this colour
        };
        return colors[rand() % (sizeof(colors) / sizeof(colors[0]))];
    };
};

std::vector<Flower> Flower::flowers;

Flower flower;
