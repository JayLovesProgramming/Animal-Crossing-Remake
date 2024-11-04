// Menu/Menu.cpp
#include "Menu.h"

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
    fscanf(file, "boxPositionX=%f\n", &boxPosition.x);
    fscanf(file, "boxPositionY=%f\n", &boxPosition.y);
    fscanf(file, "boxSizeX=%f\n", &boxSize.x);
    fscanf(file, "boxSizeY=%f\n", &boxSize.y);
    fscanf(file, "iconOffsetX=%f\n", &iconOffset.x);
    fscanf(file, "iconOffsetY=%f\n", &iconOffset.y);
    fscanf(file, "promptText=%255[^\n]", &promptText);
};

void MenuManager::LoadUIConfig()
{
    std::cout << "Opening UI config: " << configFilePath << std::endl;
    FILE *file = fopen(configFilePath, "r");

    if (file != NULL)
    {
        LoadConfigValues(file);
        fclose(file);
        lastModifiedTime = GetLastModificationTime();
        std::cout << "Loaded UI config" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open the UI config file" << std::endl;
    }
};

void MenuManager::DrawShakeTreePrompt(bool isNearTree, float alpha)
{
    if (isNearTree)
    {
        DrawRectangleRounded(
            Rectangle{boxPosition.x,
                      boxPosition.y,
                      boxSize.x,
                      boxSize.y},
            0.2f,
            10,
            Fade(DARKGRAY, alpha));

        Vector2 iconPosition = {boxPosition.x + iconOffset.x, boxPosition.y + boxSize.y / 2};

        DrawCircle(
            static_cast<int>(iconPosition.x),
            static_cast<int>(iconPosition.y),
            10.0f,
            Fade(WHITE, alpha));

        DrawText("E", static_cast<int>(iconPosition.x - 6), static_cast<int>(iconPosition.y - 10), 20, Fade(BLACK, alpha));

        Vector2 textPosition = {iconPosition.x + 30, iconPosition.y - 10};
        DrawText(promptText, static_cast<int>(textPosition.x), static_cast<int>(textPosition.y), 20, Fade(WHITE, alpha));
    }
};

void MenuManager::LiveUpdateUI()
{
    // Check for file modification and reload if necessary
    time_t currentModTime = GetLastModificationTime();
    if (currentModTime != lastModifiedTime)
    {
        std::cout << "Config file modified. Reloading..." << std::endl;
        LoadUIConfig();
        lastModifiedTime = currentModTime;
    }
};
