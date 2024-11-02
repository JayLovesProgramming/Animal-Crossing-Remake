// UI.h
// TODO: Make this a class

#pragma once

#include "raylib.h"
#include <sys/stat.h>
#include <iostream>

class UIManager
{
public:
    Vector2 boxPosition;
    Vector2 boxSize;
    Vector2 iconOffset;
    char promptText[256];
    time_t lastModifiedTime;
    constexpr static char *configFilePath = "C:/Users/jayxw/Desktop/AnimalCrossing/src/ui_config.txt";

    time_t GetLastModificationTime()
    {
        struct stat fileStat;
        if (stat(UIManager::configFilePath, &fileStat) == 0)
        {
            return fileStat.st_mtime;
        }
        return 0;
    };

    void LoadUIConfig()
    {
        std::cout << "Opening UI config: " << UIManager::configFilePath << std::endl;
        FILE *file = fopen(UIManager::configFilePath, "r");

        if (file != NULL)
        {
            LoadConfigValues(file);
            fclose(file);
            UIManager::lastModifiedTime = UIManager::GetLastModificationTime();
            std::cout << "Loaded UI config" << std::endl;
        }
        else
        {
            std::cerr << "Failed to open the UI config file" << std::endl;
        }
    };

    void DrawShakeTreePrompt(bool isNearTree, float alpha)
    {
        if (isNearTree)
        {
            DrawRectangleRounded(
                Rectangle
                {UIManager::boxPosition.x, 
                UIManager::boxPosition.y, 
                UIManager::boxSize.x,
                UIManager::boxSize.y}, 
                0.2f, 
                10, 
                Fade(DARKGRAY, alpha));

            Vector2 iconPosition = {UIManager::boxPosition.x + UIManager::iconOffset.x, UIManager::boxPosition.y + UIManager::boxSize.y / 2};

            DrawCircle(
                static_cast<int>(iconPosition.x), 
                static_cast<int>(iconPosition.y), 
                10.0f, 
                Fade(WHITE, alpha)
            );

            DrawText("E", static_cast<int>(iconPosition.x - 6), static_cast<int>(iconPosition.y - 10), 20, Fade(BLACK, alpha));

            Vector2 textPosition = {iconPosition.x + 30, iconPosition.y - 10};
            DrawText(UIManager::promptText, static_cast<int>(textPosition.x), static_cast<int>(textPosition.y), 20, Fade(WHITE, alpha));
        }
    };

    void LiveUpdateUI()
    {
        // Check for file modification and reload if necessary
        time_t currentModTime = UIManager::GetLastModificationTime();
        if (currentModTime != UIManager::lastModifiedTime)
        {
            std::cout << "Config file modified. Reloading..." << std::endl;
            UIManager::LoadUIConfig();
            UIManager::lastModifiedTime = currentModTime;
        }
    }

private:
    void LoadConfigValues(FILE *file)
    {
        fscanf(file, "boxPositionX=%f\n", &boxPosition.x);
        fscanf(file, "boxPositionY=%f\n", &boxPosition.y);
        fscanf(file, "boxSizeX=%f\n", &boxSize.x);
        fscanf(file, "boxSizeY=%f\n", &boxSize.y);
        fscanf(file, "iconOffsetX=%f\n", &iconOffset.x);
        fscanf(file, "iconOffsetY=%f\n", &iconOffset.y);
        fscanf(file, "promptText=%255[^\n]", promptText);
    }
};

UIManager uiManager;
