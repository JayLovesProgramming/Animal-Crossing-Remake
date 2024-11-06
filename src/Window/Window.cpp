// Window/Window.cpp
#include "Window.h"

#include "raylib.h"
#include <iostream>
using std::cout, std::endl;

bool WindowManager::PressedExit() // Check if a exit key is pressed. Used to exit and destroy the window
{
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE); // ESC or Backspace (Should be debug only but on release remove this check)
}

void WindowManager::ResetValues(bool resetPreviousScreen)
{
    if (resetPreviousScreen)
    {
        prevScreenWidth = screenWidth;
        prevScreenHeight = screenHeight;
    }
    else
    {
        screenWidth = prevScreenWidth;
        screenHeight = prevScreenHeight;
    }
}

void WindowManager::HandleAltEnterWindowMode()
{
    int monitor = GetCurrentMonitor();
    bool altEnterPressed = (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)));
    if (altEnterPressed)
    {
        if (!IsWindowFullscreen())
        {
            // if we are not full screen, set the window size to match the monitor we are on
            ResetValues(true);
            int monitorWidth = GetMonitorWidth(monitor);
            int monitorHeight = GetMonitorHeight(monitor);
            SetWindowSize(monitorWidth, monitorHeight);
            ToggleFullscreen();
            screenWidth = monitorWidth;
            screenHeight = monitorHeight;
        }
        else
        {
            // if we are full screen, then go back to the windowed size
            ToggleFullscreen();
            if (prevScreenWidth != NULL && prevScreenHeight != NULL)
            {
                SetWindowSize(prevScreenWidth, prevScreenHeight);
                ResetValues(false);
            }
            else
            {
                SetWindowSize(screenWidth, screenHeight);
            }
        }
    }
}

void WindowManager::HandleWindow()
{
    HandleAltEnterWindowMode();
    // cout << "LOOP" << endl;
}

void WindowManager::InitGameWindowIcon() // Inits the window icon and sets it
{
    Image windowIcon = LoadImage("../src/Assets/Textures/leaf.png"); // Loads the window icon
    SetWindowIcon(windowIcon);                                       // Sets the window icon
};

void WindowManager::EnableVsync(bool fallback)
{
    if (fallback)
    {
        cout << "[VSYNC]: Fallback so disabled" << endl;
    }
    else
    {
        cout << "[VSYNC]: Enabled" << endl;
    }
    SetWindowState(FLAG_VSYNC_HINT); // Enables V-Sync
    isVsync = true;
}

void WindowManager::DisableVsync()
{
    cout << "[VSYNC]: Disabled" << endl;
    SetTargetFPS(targetFPS); // Sets the TARGET FPS
}

void WindowManager::CheckForVSync()
{
    isVsync = false;
    int currentMonitor = GetCurrentMonitor(); // 0 is typically the primary monitor on their OS
    int currentMonitorRefreshRate = GetMonitorRefreshRate(currentMonitor);

    cout << "[MONITOR]: " << currentMonitor << endl;
    cout << "[REFRESH RATE]: " << currentMonitorRefreshRate << endl;

    if (targetFPS == currentMonitorRefreshRate)
    {
        EnableVsync(false);
    }
    else if (targetFPS > currentMonitorRefreshRate || targetFPS < currentMonitorRefreshRate)
    {
        DisableVsync();
    }
    else // Fallback, just enable v sync
    {
        EnableVsync(true);
    }
}

void WindowManager::InitWindowAndSetFlags()
{
    InitWindow(screenWidth, screenHeight, windowName); // Init a window with a screen width, height and window name
    SetTraceLogLevel(LOG_ERROR);
    InitGameWindowIcon(); // Init a window icon
    // Set some flags for the window
    SetWindowState(FLAG_WINDOW_RESIZABLE); // Makes the window resizeable
    // SetWindowMonitor(1);                   // Sets the window to your primary application. To be tested
    CheckForVSync();

    SetWindowState(FLAG_WINDOW_ALWAYS_RUN); // Will run even if minimised
    // SetWindowState(FLAG_WINDOW_TRANSPARENT);
    HideCursor();
    // SetWindowState(FLAG_FULLSCREEN_MODE);
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_HIGHDPI);
    // SetMouseCursor(0);
    SetExitKey(0); // Removes all defaults for Exit key so I can create my own.
};
