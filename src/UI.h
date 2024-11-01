// UI.h
// TODO: Make this a class

#pragma once

#include "raylib.h"
#include <sys/stat.h>
#include <iostream>

struct UIConfig
{
    Vector2 boxPosition;
    Vector2 boxSize;
    Vector2 iconOffset;
    char promptText[256];
};
UIConfig uiConfig;
time_t lastModifiedTime;
const char *configFilePath = "../src/ui_config.txt";

time_t GetLastModificationTime(const char *filename)
{
    struct stat fileStat;
    if (stat(filename, &fileStat) == 0)
    {
        return fileStat.st_mtime;
    }
    return 0;
}

UIConfig LoadUIConfig(const char *filename)
{
    UIConfig config;
    std::cout << "Opening UI config: " << filename << std::endl;
    FILE *file = fopen(filename, "r");

    if (file != NULL)
    {
        if (fscanf(file, "boxPositionX=%f\n", &config.boxPosition.x) != 1 ||
            fscanf(file, "boxPositionY=%f\n", &config.boxPosition.y) != 1 ||
            fscanf(file, "boxSizeX=%f\n", &config.boxSize.x) != 1 ||
            fscanf(file, "boxSizeY=%f\n", &config.boxSize.y) != 1 ||
            fscanf(file, "iconOffsetX=%f\n", &config.iconOffset.x) != 1 ||
            fscanf(file, "iconOffsetY=%f\n", &config.iconOffset.y) != 1 ||
            fscanf(file, "promptText=%255[^\n]", config.promptText) != 1)
        {
            std::cout << "Error reading config values." << std::endl;
        }
        else
        {
            std::cout << "Loaded UI config" << std::endl;
        }
        fclose(file);
    }
    else
    {
        std::cout << "Failed to load the file" << std::endl;
    }
    return config;
}

void DrawShakeTreePrompt(bool isNearTree, float alpha, UIConfig config)
{
    if (isNearTree)
    {
        // std::cout << "Drawing UI prompt" << std::endl;
        // std::cout << config.boxSize.x << ", " << config.boxSize.y << std::endl;
        DrawRectangleRounded(Rectangle{config.boxPosition.x, config.boxPosition.y, config.boxSize.x, config.boxSize.y}, 0.2, 10, Fade(DARKGRAY, alpha));
        Vector2 iconPosition = {config.boxPosition.x + config.iconOffset.x, config.boxPosition.y + config.boxSize.y / 2};
        DrawCircle(iconPosition.x, iconPosition.y, 10, Fade(WHITE, alpha));
        DrawText("E", iconPosition.x - 6, iconPosition.y - 10, 20, Fade(BLACK, alpha));

        Vector2 textPosition = {iconPosition.x + 30, iconPosition.y - 10};
        DrawText(config.promptText, textPosition.x, textPosition.y, 20, Fade(WHITE, alpha));
    }
}
