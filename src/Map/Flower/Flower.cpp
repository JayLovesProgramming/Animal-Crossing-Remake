// Flower/Flower.cpp
#include "Flower.h"

void Flower::LoadFlowers()
{
    if (numberOfFlowers == 0)
        return;

    srand(static_cast<unsigned>(time(0)));
    flowerModel = LoadModel("../src/Assets/Models/plant/scene.gltf");
    assert(flowerModel.meshCount > 0);
    GenerateRandomFlowers(numberOfFlowers);
    std::cout << "[LOADED]: " << numberOfFlowers << " Flowers" << std::endl;
};

void Flower::DrawFlowers()
{
    if (numberOfFlowers != 0)
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
            Map::GetHeightAtPosition(flowerX, flowerZ),
            flowerZ};
        flower.color = GenerateRandomFlowerColour();
        flowers.push_back(flower);
    }
};

void Flower::UnloadFlowers()
{
    UnloadModel(flowerModel);
    std::cout << "[UNLOADED]: " << numberOfFlowers << " Flowers" << std::endl;
};

Color Flower::GenerateRandomFlowerColour()
{
    Color colours[] = {
        YELLOW,
        PINK,
    };
    return colours[rand() % (sizeof(colours) / sizeof(colours[0]))];
};