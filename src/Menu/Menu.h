// UI/UI.h
#pragma once

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "raylib.h" // Assuming you're using raylib for graphics

class MenuManager
{
public:
    static time_t GetLastModificationTime();
    static void LoadConfigValues(FILE *file);

    inline static Vector2 boxPosition;
    inline static Vector2 boxSize;
    inline static Vector2 iconOffset;
    inline static char promptText[256];
    inline static const char *configFilePath = "C:/Users/jayxw/Desktop/AnimalCrossing/src/ui_config.txt";
    inline static time_t lastModifiedTime;

    static void LoadUIConfig();
    static void DrawShakeTreePrompt(bool isNearTree, float alpha);
    static void LiveUpdateUI();
};
