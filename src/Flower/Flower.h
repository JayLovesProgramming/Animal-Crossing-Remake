// Flower/Flower.h
#pragma once


class Flower
{
public:
    Vector3 position;
    Color color = WHITE;
    float scale = 0.015f;
    inline static Model flowerModel;
    inline static std::vector<Flower> flowers;
    const static int numberOfFlowers = 100;

    static void LoadFlowers()
    {
        if (numberOfFlowers == 0)
            return;

        srand(static_cast<unsigned>(time(0)));
        flowerModel = LoadModel("../src/Assets/Models/plant/scene.gltf");
        assert(flowerModel.meshCount != 0);
        GenerateRandomFlowers(numberOfFlowers, 50.0f, 50.0f);
    }

    static void DrawFlowers()
    {
        if (numberOfFlowers != 0)
        {
            for (const Flower &flower : flowers)
            {
                DrawModel(flowerModel, flower.position, flower.scale, flower.color);
            }
        }
    }

    static void GenerateRandomFlowers(int count, float xRange, float zRange)
    {
        Flower flower;
        for (int i = 0; i < count; ++i)
        {
            float flowerX = static_cast<float>(rand()) / RAND_MAX * xRange - (xRange / 2);
            float flowerZ = static_cast<float>(rand()) / RAND_MAX * zRange - (zRange / 2);
            flower.position = {
                flowerX,
                SurfaceManager::GetHeightAtPosition(flowerX, flowerZ),
                flowerZ};
            flower.color = GenerateRandomFlowerColour();
            flowers.push_back(flower);
        }
    }

    static void UnloadFlowers()
    {
        UnloadModel(flowerModel);
        std::cout << "[UNLOADED]: Flowers" << std::endl;
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
