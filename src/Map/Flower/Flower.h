// Flower/Flower.h
#pragma once

class Flower
{
public:
    Vector3 position;
    Color color;
    float scale = 0.012f;
    inline static Model flowerModel;

    inline static std::vector<Flower> flowers;
    
    const static int numberOfFlowers = 5000;
    inline const static auto xRange = 900.0f;
    inline const static auto zRange = 900.0f;
    static constexpr auto flowerCollisionRadius = 3.5f;

    static void LoadFlowers();

    static void DrawFlowers();

    inline static void GenerateFlowers(int count);

    inline static void UnloadFlowers();

    static void HandleFlowerCollision();

private:
    static Color GenerateRandomFlowerColour();
    
    inline static float flowerHeightThreshold = 15.0f;
};
