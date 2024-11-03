// Main.cpp
#include "Main.h"

// Ends the drawing loop and draws some other things outside of the main game draw
void EndDrawingLoop()
{
    EndMode3D(); // End the 3D mode so we can then draw other UI on top
    
    // std::cout << screenWidth << std::endl;
    DrawText(TextFormat("FPS: %i", GetFPS()), screenWidth - 220, screenHeight - 100, 30, GREEN); // Draws the current FPS

    // uiManager.DrawShakeTreePrompt(true, 250.0f); // Draws some simple UI for shaking the tree

    EndDrawing();   // Ends the canvas drawing and swap buffers
}

// Initalizes the game
void InitGame()
{
    SetTraceLogLevel(LOG_WARNING);
    // uiManager.LoadUIConfig(); // Loads the UI config when the game initalizes TODO: Init this in UI.h

    InitWindow(screenWidth, screenHeight, "Animal Crossing - Dev Build"); // Init a window with a screen width, height and window name
    WindowManager::SetWindowFlags();

    CharacterCamera::InitCamera(); // Init the camera for the character TODO: Init this in the Camera.h
    
    Tree::LoadTrees();    // Init and load the trees for the map TODO: Init and load this in Tree.h

    Flower::LoadFlowers(); // Init and load the flowers TOOD: Init and load this in Flower.h

    Grass::LoadGrassTexture();
}

// The main game draw loop. This draws everything you see on the screen
void DrawLoop(Vector3 characterPosition, SurfaceManager grounds[GRID_SIZE][GRID_SIZE])
{
    // Begin the drawing, 3D mode and blend mode
    BeginDrawing();
    BeginMode3D(CharacterCamera::camera);

    ClearBackground(BLACK); // Clears the background every frame
    
    characterPosition.y = SurfaceManager::GetHeightAtPosition(characterPosition.x, characterPosition.z);

    Flower::DrawFlowers(); // Draws the flowers on the map

    Tree::DrawTrees(); // Draws the trees on the map

    SurfaceManager::DrawGround();

    // uiManager.LiveUpdateUI(); // Checks if the UI txt file gets updated and then updates it if it needs to
    DrawCube(characterPosition, 1.0f, 2.0f, 1.0f, PINK); // Draw a pink cube for the character. TODO: Replace with a actual Model

    EndDrawingLoop();
}

int main(void)
{
    InitGame(); // A main function to initalize all the shit we need

    Grass grass;                
    SurfaceManager::GenerateGroundSurface(grass.grassTexture); // Generates the surfaces planes

    while (!WindowShouldClose())
    {
        MouseManager::UpdateMousePosition();
        WindowManager::HandleWindow();
        DrawLoop(Character::characterPosition, grounds); // Main game draw loop

        GameControls::UpdateControls(&Character::characterPosition, Character::characterSpeed);

        CharacterCamera::UpdateCamera(&Character::characterPosition);

        if (WindowManager::PressedExit()) // Check for a specific key and exit the game
        {
            break;
        }
    }
    return 0;
}

// TODO: Keep the Main less than 150 lines
