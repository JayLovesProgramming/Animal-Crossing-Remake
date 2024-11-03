// Window/Window.h
#pragma once

static int screenWidth = 1280;
static int screenHeight = 720;
const static auto targetFPS = 200;
static int prevScreenWidth;
static int prevScreenHeight;

class WindowManager
{
public:
    static bool PressedExit() // Check if a exit key is pressed. Used to exit and destroy the window
    {
        return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE); // ESC or Backspace (Should be debug only but on release remove this check)
    }

    static void ResetValues(bool resetPreviousScreen)
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

    static void HandleAltEnterWindowMode()
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

    static void HandleWindow()
    {
        HandleAltEnterWindowMode();
    }

    static void InitGameWindowIcon() // Inits the window icon and sets it
    {
        Image windowIcon = LoadImage("../src/Assets/Textures/icon.png"); // Loads the window icon
        SetWindowIcon(windowIcon);                                       // Sets the window icon
    };

    static void CheckForVSync()
    {
        int currentMonitorRefreshRate = GetMonitorRefreshRate(GetCurrentMonitor());

        if (targetFPS > currentMonitorRefreshRate)
        {
            std::cout << "VSYNC: Disabled" << std::endl;
            SetTargetFPS(targetFPS); // Sets the TARGET FPS
        }
        else
        {
            std::cout << "VSYNC: Enabled" << std::endl;
            SetWindowState(FLAG_VSYNC_HINT); // Enables V-Sync
        }
    }

    static void SetWindowFlags()
    {
        InitGameWindowIcon(); // Init a window icon
        // Set some flags for the window
        SetWindowState(FLAG_WINDOW_RESIZABLE); // Makes the window resizeable
        SetWindowMonitor(0);                   // Sets the window to your primary application. To be tested
        CheckForVSync();
        SetWindowState(FLAG_WINDOW_ALWAYS_RUN); // Will run even if minimised
        // SetWindowState(FLAG_WINDOW_TRANSPARENT);
        HideCursor();
        // SetWindowState(FLAG_FULLSCREEN_MODE);
        // SetConfigFlags(FLAG_MSAA_4X_HINT);
        // SetMouseCursor(0);
        SetExitKey(0); // Removes all defaults for Exit key so I can create my own.
    };
};
