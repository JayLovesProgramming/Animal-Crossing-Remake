// Window/Window.h
#pragma once

class WindowManager
{
public:
    inline static int screenWidth = 1280;
    inline static int screenHeight = 720;
    inline static int targetFPS = 200;
    inline static int prevScreenWidth;
    inline static int prevScreenHeight;
    inline static const char windowName[] = "Animal Crossing - Development Build (Alpha 0.0.1)";

    static bool PressedExit(); // Check if a exit key is pressed. Used to exit and destroy the window

    static void ResetValues(bool resetPreviousScreen);

    static void HandleAltEnterWindowMode();

    static void HandleWindow();

    static void InitGameWindowIcon(); // Inits the window icon and sets it

    static void CheckForVSync();

    static void SetWindowFlags();
};
