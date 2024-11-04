// Window/Window.h
#pragma once

#include <string>

class WindowManager
{
public:
    static int screenWidth;
    static int screenHeight;
    static int targetFPS;
    static int prevScreenWidth;
    static int prevScreenHeight;
    static const char windowName[];

    static bool PressedExit(); // Check if a exit key is pressed. Used to exit and destroy the window

    static void ResetValues(bool resetPreviousScreen);

    static void HandleAltEnterWindowMode();

    static void HandleWindow();

    static void InitGameWindowIcon(); // Inits the window icon and sets it

    static void CheckForVSync();

    static void SetWindowFlags();
};

int WindowManager::screenWidth = 1280;
int WindowManager::screenHeight = 720;
int WindowManager::targetFPS = 200;
int WindowManager::prevScreenWidth;
int WindowManager::prevScreenHeight;
const char WindowManager::windowName[] = "Animal Crossing - Development Build (Alpha 0.0.1)";
