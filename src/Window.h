// Window.h
#pragma once 

const static int screenWidth = 1280;
const static int screenHeight = 720;

bool PressedExit() // Check if a exit key is pressed. Used to exit and destroy the window
{
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE); // ESC or Backspace (Should be debug only but on release remove this check)
}

void InitGameWindowIcon() // Inits the window icon and sets it
{
    Image windowIcon = LoadImage("../src/Assets/Textures/icon.png"); // Loads the window icon
    SetWindowIcon(windowIcon); // Sets the window icon
};
