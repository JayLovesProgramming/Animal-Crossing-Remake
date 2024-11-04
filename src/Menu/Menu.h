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

    static Vector2 boxPosition;
    static Vector2 boxSize;
    static Vector2 iconOffset;
    static char promptText[256];
    static char *configFilePath;
    static time_t lastModifiedTime;

    static void LoadUIConfig();
    static void DrawShakeTreePrompt(bool isNearTree, float alpha);
    static void LiveUpdateUI();
};

Vector2 MenuManager::boxPosition;
Vector2 MenuManager::boxSize;
Vector2 MenuManager::iconOffset;
char MenuManager::promptText[256];
char *MenuManager::configFilePath = "C:/Users/jayxw/Desktop/AnimalCrossing/src/ui_config.txt";
time_t MenuManager::lastModifiedTime;
