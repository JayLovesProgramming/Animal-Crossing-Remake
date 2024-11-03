// UI/UI.h
#pragma once

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "raylib.h" // Assuming you're using raylib for graphics

class UIManager {
public:
    time_t GetLastModificationTime();
    void LoadConfigValues(FILE *file);

    Vector2 boxPosition;
    Vector2 boxSize;
    Vector2 iconOffset;
    char promptText[256];
    const char *configFilePath = "C:/Users/jayxw/Desktop/AnimalCrossing/src/ui_config.txt";
    time_t lastModifiedTime;
    
    void LoadUIConfig();
    void DrawShakeTreePrompt(bool isNearTree, float alpha);
    void LiveUpdateUI();

private:

};

UIManager uiManager;
