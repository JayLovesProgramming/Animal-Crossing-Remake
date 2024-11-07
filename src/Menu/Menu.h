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

    inline static int buttonState = 0;
    inline static bool buttonPressed = false;

    static void InitalizeButton();
    static time_t GetLastModificationTime();
    static void LoadConfigValues(FILE *file);
    static void LoadUIConfig();
    static void DrawShakeTreePrompt();
    static void LiveUpdateUI();
    static void CheckForButtonPress();
    inline static Sound fxButtonSound;
    inline static Texture2D button;

    inline static Rectangle sourceRec;
    inline static Rectangle buttonBounds;

    inline static float frameHeight;
};
