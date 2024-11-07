// Flower/Flower.h
#pragma once

class Flower
{
public:
    Vector3 position;
    Color color;
    float scale = 0.015f;
    inline static Model flowerModel;

    inline static std::vector<Flower> flowers;
    
    const static int numberOfFlowers = 2500;
    inline const static auto xRange = 500.0f;
    inline const static auto zRange = 500.0f;
    static constexpr auto flowerCollisionRadius = 1.5f;
    inline static float flowerHeightThreshold = 55.0f;

    inline static void LoadFlowers();

    inline static void DrawFlowers();

    inline static void GenerateRandomFlowers(int count);

    inline static void UnloadFlowers();

    inline static void HandleFlowerCollision();

private:
    static Color GenerateRandomFlowerColour();
};
