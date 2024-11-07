// Main.cpp
#include "Main.h"

// Ends the drawing loop and draws some other things outside of the main game draw
void Main::EndDrawingLoop()
{
    EndMode3D();                                                                                                               // End the 3D mode so we can then draw other UI on top
    DrawText(TextFormat("FPS: %i", GetFPS()), WindowManager::screenWidth - 220, WindowManager::screenHeight - 100, 30, GREEN); // Draws the current FPS
    MenuManager::CheckForButtonPress();
    EndDrawing();                                                                                                              // Ends the canvas drawing and swap buffers
}

// Initalizes the game
bool Main::InitGame()
{
    WindowManager::InitWindowAndSetFlags();

    MenuManager::LoadUIConfig(); // Loads the UI config when the game initalizes TODO: Init this in UI.h
    MenuManager::InitalizeButton();

    Character::LoadCharacterModel();

    CharacterCamera::InitCamera(); // Init the camera for the character TODO: Init this in the Camera.h

    Tree::LoadTrees(); // Init and load the trees for the map TODO: Init and load this in Tree.h

    Flower::LoadFlowers(); // Init and load the flowers TOOD: Init and load this in Flower.h

    Grass::LoadGrassTexture();
    Map::GenerateGroundSurface(); // Generates the surfaces planes
    return true;
}

void Main::UpdatePostDrawLoop()
{
    CharacterCamera::UpdateCamera(&Character::characterPos);
    MouseManager::UpdateMousePosition();
    WindowManager::HandleWindow();
    MouseManager::ToggleMouseCursor();
    GameControls::UpdateControls(&Character::characterPos, Character::characterSpeed);
}

// The main game draw loop. This draws everything you see on the screen
void Main::DrawLoop()
{
    // Begin the drawing, 3D mode and blend mode
    BeginDrawing();
        ClearBackground(BLANK); // Clears the background every frame
        BeginMode3D(CharacterCamera::camera);
        rlEnableBackfaceCulling();
        // Draw world elements
        Tree::DrawTrees();     // Draws the trees on the map
        Flower::DrawFlowers(); // Draws the flowers on the map
        Map::DrawGround();
        Character::DrawCharacter();

    EndDrawingLoop();
}

int Main::Run()
{
    assert(InitGame());

    while (!WindowShouldClose())
    {
        DrawLoop(); // Main game draw loop
        UpdatePostDrawLoop();

        if (WindowManager::PressedExit()) // Check for a specific key and exit the game
            break;
    }

    return 0;
}

int main()
{
    return Main::Run();
}
