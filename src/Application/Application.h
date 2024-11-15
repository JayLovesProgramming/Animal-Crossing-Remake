#pragma once

class Application
{

public:
    static void Run();
    ~Application();

private:
    static bool InitializeGame();
    static void DrawLoop();
    static void UpdateGame();
    static void EndDrawingLoop();
};
