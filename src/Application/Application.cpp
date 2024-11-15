#include "Application.h"

#include "LoadOnce.h"

void Application::Run()
{
    assert(InitializeGame());

    while (!WindowShouldClose())
    {
        DrawLoop(); // Main game draw loop
        UpdateGame();

        if (WindowManager::PressedExit()) // Check for a specific key and exit the game
            break;
    }
};

// Initalizes the game
bool Application::InitializeGame()
{
    WindowManager::InitializeWindow();

    // ShaderManager::InitializeSkyboxLighting(); // Figure out this later on

    // MenuManager::LoadUIConfig(); // Loads the UI config when the game initalizes TODO: Init this in UI.h
    MenuManager::InitalizeButton();

    Character::LoadCharacterModel();

    CharacterCamera::InitalizeCamera(); // Init the camera for the character TODO: Init this in the Camera.h

    Grass::LoadGrassTexture();

    Map::GenerateGroundSurface(); // Generates the surfaces planes

    Tree::LoadTrees(); // Init and load the trees for the map TODO: Init and load this in Tree.h

    Flower::LoadFlowers(); // Init and load the flowers TOOD: Init and load this in Flower.h

    return true;
}

void Application::UpdateGame()
{
    CharacterCamera::UpdateCamera(&Character::characterPos);
    MouseManager::UpdateMousePosition();
    WindowManager::HandleWindow();
    MouseManager::ToggleMouseCursor();
    // ShaderManager::UpdateSkyboxLighting(); // Figure this later on
    GameControls::UpdateControls(&Character::characterPos, Character::characterSpeed);
    AudioManager::ManageMainMusic();
}

// The main game draw loop. This draws everything you see on the screen
void Application::DrawLoop()
{
    // Begin the drawing, 3D mode and blend mode
    BeginDrawing();
    ClearBackground(RAYWHITE); // Clears the background every frame
    BeginShaderMode(ShaderManager::skyBoxShader);
    BeginMode3D(CharacterCamera::camera);
    rlEnableBackfaceCulling();
    // Draw world elements
    Flower::DrawFlowers(); // Draws the flowers on the map
    Tree::DrawTrees();     // Draws the trees on the map
    Map::DrawGround();
    Character::DrawCharacter();
    EndDrawingLoop();
}

// Ends the drawing loop and draws some other things outside of the main game draw
void Application::EndDrawingLoop()
{
    EndMode3D();  
    EndShaderMode();                                                                                                             // End the 3D mode so we can then draw other UI on top
    DrawText(TextFormat("FPS: %i", GetFPS()), WindowManager::screenWidth - 220, WindowManager::screenHeight - 100, 30, GREEN); // Draws the current FPS
    MenuManager::CheckForButtonPress();
    EndDrawing();                                                                                                              // Ends the canvas drawing and swap buffers
}

Application::~Application()
{
    Flower::UnloadFlowers();
    Tree::UnloadTrees();
    Map::UnloadGround();
    Grass::UnloadGrassTexture();
    AudioManager::UnloadAudio();
    Character::UnloadCharacterModel();
    CloseWindow(); // Finally close the window
    std::cout << destroyedString << "Game State" << std::endl;
}
