// Flower/Flower.h
#pragma once

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
