// Menu/Menu.cpp
#include "Menu.h"

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "raylib.h" 
#include "Controls/Controls.h" 
#include "Window/Window.h" 
#include "Audio/Audio.h" 

using std::cout, std::cerr, std::endl;

void MenuManager::InitalizeButton()
{
    cout << "Initializing button" << endl;
    int NUM_FRAMES = 3;
    button = LoadTexture("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Textures/button.png");
    frameHeight = (float)button.height / NUM_FRAMES;
    sourceRec = {0, 0, (float)button.width, frameHeight};
    buttonBounds = {WindowManager::screenWidth / 2.0f, WindowManager::screenHeight / 2.0f - button.height / NUM_FRAMES / 2.0f, (float)button.width, frameHeight};

    fxButtonSound = LoadSound("C:/Users/jayxw/Desktop/AnimalCrossing/src/Assets/Sounds/buttonfx.wav");
    cout << "Initialized button" << endl;
};

void MenuManager::CheckForButtonPress()
{
    if (!GameControls::nearTree)
        return;
        
    if (IsKeyDown(KEY_E))
    {
        buttonState = 2;
    }
    else
    {
        buttonState = 1;
    }

    if (IsKeyReleased(KEY_E))
    {
        buttonPressed = true;
    }
    else
    {
        buttonPressed = false;
    }

    if (buttonPressed)
    {
        PlaySound(fxButtonSound);
    }

    sourceRec.y = buttonState * frameHeight;
    DrawTextureRec(button, sourceRec, Vector2{buttonBounds.x, buttonBounds.y}, WHITE);
};


time_t MenuManager::GetLastModificationTime()
{
    struct stat fileStat;
    if (stat(configFilePath, &fileStat) == 0)
    {
        return fileStat.st_mtime;
    }
    return 0;
};

void MenuManager::LoadConfigValues(FILE *file)
{
    fscanf(file, "boxPositionX=%f/n", &boxPosition.x);
    fscanf(file, "boxPositionY=%f/n", &boxPosition.y);
    fscanf(file, "boxSizeX=%f/n", &boxSize.x);
    fscanf(file, "boxSizeY=%f/n", &boxSize.y);
    fscanf(file, "iconOffsetX=%f/n", &iconOffset.x);
    fscanf(file, "iconOffsetY=%f/n", &iconOffset.y);
    fscanf(file, "promptText=%255[^/n]", &promptText);
};

void MenuManager::LoadUIConfig()
{
    cout << "Opening UI config: " << configFilePath << endl;
    FILE *file = fopen(configFilePath, "r");

    if (file != NULL)
    {
        LoadConfigValues(file);
        fclose(file);
        lastModifiedTime = GetLastModificationTime();
        cout << "Loaded UI config" << endl;
    }
    else
    {
        cerr << "Failed to open the UI config file" << endl;
    }
};

void MenuManager::DrawShakeTreePrompt()
{
    if (GameControls::nearTree)
    {
        DrawRectangleRounded(
            Rectangle{boxPosition.x,
                      boxPosition.y,
                      boxSize.x,
                      boxSize.y},
            0.2f,
            10,
            Fade(RAYWHITE, 10.0f));

        Vector2 iconPosition = {boxPosition.x + iconOffset.x, boxPosition.y + boxSize.y / 2};

        // DrawRectangleRounded(
        //     Rectangle{static_cast<float>(iconPosition.x),
        //               static_cast<float>(iconPosition.y),
        //                 20.0f,
        //               20}, 0.2f, 10, Fade(RED, 10.0f));
            

        DrawCircle(
            static_cast<int>(iconPosition.x),
            static_cast<int>(iconPosition.y),
            15.0f,
            Fade(RED, 20.0f));

        DrawText("E", static_cast<int>(iconPosition.x - 6), static_cast<int>(iconPosition.y - 10), 20, Fade(BLACK, 20.0f));

        Vector2 textPosition = {iconPosition.x + 30, iconPosition.y - 10};
        DrawText(promptText, static_cast<int>(textPosition.x), static_cast<int>(textPosition.y), 20, Fade(BLACK, 20.0f));
    }
};

void MenuManager::LiveUpdateUI()
{
    // Check for file modification and reload if necessary
    time_t currentModTime = GetLastModificationTime();
    if (currentModTime != lastModifiedTime)
    {
        cout << "Config file modified. Reloading..." << endl;
        LoadUIConfig();
        lastModifiedTime = currentModTime;
    }
};
