// Main.cpp
#include "Main.h"

// Ends the drawing loop and draws some other things outside of the main game draw
void EndDrawingLoop()
{
    EndMode3D(); // End the 3D mode so we can then draw other UI on top

    DrawText(TextFormat("FPS: %i", GetFPS()), screenWidth - 220, screenHeight - 100, 30, GREEN); // Draws the current FPS

    uiManager.DrawShakeTreePrompt(true, 250.0f); // Draws some simple UI for shaking the tree

    EndDrawing();   // Ends the canvas drawing and swap buffers
    EndBlendMode(); // Used to end the blending mode - blending modes are used to control how colours and transparency are handled when drawing shapes, textures and other graphical elements on top of each other
}

// Initalizes the game
void InitGame()
{
    uiManager.LoadUIConfig(); // Loads the UI config when the game initalizes TODO: Init this in UI.h

    InitWindow(screenWidth, screenHeight, "Animal Crossing - Dev Build"); // Init a window with a screen width, height and window name
    SetWindowFlags();

    characterCamera.InitCamera(); // Init the camera for the character TODO: Init this in the Camera.h
    trees.LoadTrees();    // Init and load the trees for the map TODO: Init and load this in Tree.h
    flower.LoadFLowers(); // Init and load the flowers TOOD: Init and load this in Flower.h
}

// The main game draw loop. This draws everything you see on the screen
void DrawLoop(Vector3 characterPosition, GroundTile grounds[GRID_SIZE][GRID_SIZE])
{
    // Begin the drawing, 3D mode and blend mode
    BeginDrawing();
    BeginMode3D(characterCamera.camera);
    BeginBlendMode(BLEND_ALPHA);

    ClearBackground(BLACK); // Clears the background every frame

    flower.DrawFlowers(); // Draws the flowers on the map

    trees.DrawTrees(); // Draws the trees on the map

    uiManager.LiveUpdateUI(); // Checks if the UI txt file gets updated and then updates it if it needs to

    DrawCube(characterPosition, 1.0f, 2.0f, 1.0f, PINK); // Draw a pink cube for the character. TODO: Replace with a actual Model

    // Gets the info for the ground/surface and draws it on the screen
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int z = 0; z < GRID_SIZE; z++)
        {
            if (WIRE_FLOOR)
            {
                DrawModelWires(grounds[x][z].model, grounds[x][z].position, 1.0f, WHITE);
            }
            else
            {
                DrawModel(grounds[x][z].model, grounds[x][z].position, 1.0f, WHITE);
            }
        }
    }
    EndDrawingLoop();
}

// Unloads everything when we destroy the window
void UnloadEverything(GroundTile grounds[GRID_SIZE][GRID_SIZE])
{
    UnloadModel(flower.flowerModel); // TODO: Move this to Flower.h and make it execute as a destructor

    trees.UnloadTrees(); // TODO: Move this to Tree.h and make it execute as a destructor

    // TODO: Ensure the ground is unloaded properly
    // Unload the ground
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int z = 0; z < GRID_SIZE; z++)
        {
            UnloadModel(grounds[x][z].model);
        }
    }

    CloseWindow(); // Finally close the window
}

int main(void)
{
    InitGame(); // A main function to initalize all the shit we need

    Grass grass;                                       // TODO: Fix this. Move it from here
    GenerateCurvedGround(grounds, grass.grassTexture); // Generates the surfaces planes

    while (!WindowShouldClose())
    {

        DrawLoop(characterPosition, grounds); // Main game draw loop
        gameControls.UpdateControls(&characterPosition, characterSpeed);
        characterCamera.UpdateCamera(&characterPosition);
        
        if (PressedExit()) // Check for a specific key and exit the game
        {
            break;
        }
    }
    UnloadEverything(grounds); // TODO: Create a game instance for the ENTIRE game and make use of the destructors
    return 0;
}

// TODO: Keep the Main less than 150 lines
