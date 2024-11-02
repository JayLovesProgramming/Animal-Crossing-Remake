// Window.h
#pragma once 

const static int screenWidth = 1280;
const static int screenHeight = 720;
const static auto targetFPS = 100;

// TODO: Make a class

bool PressedExit() // Check if a exit key is pressed. Used to exit and destroy the window
{
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE); // ESC or Backspace (Should be debug only but on release remove this check)
}

void InitGameWindowIcon() // Inits the window icon and sets it
{
    Image windowIcon = LoadImage("../src/Assets/Textures/icon.png"); // Loads the window icon
    SetWindowIcon(windowIcon); // Sets the window icon
};

void checkForVSync()
{
    int currentMonitor = GetCurrentMonitor();
    int currentMonitorRefreshRate = GetMonitorRefreshRate(currentMonitor);

    if (targetFPS >= currentMonitorRefreshRate)
    {
        SetTargetFPS(targetFPS); // Sets the TARGET FPS
    }
    else
    {
        SetWindowState(FLAG_VSYNC_HINT);        // Enables V-Sync
    }
}

void SetWindowFlags()
{
    InitGameWindowIcon();                                                 // Init a window icon
    // Set some flags for the window
    SetWindowState(FLAG_WINDOW_RESIZABLE);  // Makes the window resizeable
    SetWindowMonitor(0);                    // Sets the window to your primary application. To be tested

    checkForVSync();

    SetWindowState(FLAG_WINDOW_ALWAYS_RUN); // Will run even if minimised
    SetWindowState(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetExitKey(0);    // Removes all defaults for Exit key so I can create my own.
};
