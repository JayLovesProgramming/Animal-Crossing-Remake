// UI/UI.h
#pragma once

class MenuManager
{
public:
    inline static Vector2 boxPosition;
    inline static Vector2 boxSize;
    inline static Vector2 iconOffset;
    inline static char promptText[256];
    inline static const char *configFilePath = "C:/Users/jayxw/Desktop/AnimalCrossing/src/ui_config.txt";
    inline static time_t lastModifiedTime;

    static time_t GetLastModificationTime();
    static void LoadConfigValues(FILE *file);
    static void LoadUIConfig();
    static void DrawShakeTreePrompt();
    static void LiveUpdateUI();
};
