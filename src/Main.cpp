// Main.cpp
#include "Main.h"

// Generates a curved surface ? Randomized?
void GenerateCurvedGround(GroundTile grounds[GRID_SIZE][GRID_SIZE], Texture2D grassTexture)
{
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int z = 0; z < GRID_SIZE; z++)
        {
            float xOffset = (x - GRID_SIZE / 2) * GROUND_SIZE;
            float zOffset = (z - GRID_SIZE / 2) * GROUND_SIZE;

            Mesh mesh = GenMeshPlane(GROUND_SIZE, GROUND_SIZE, 10, 10);
            for (int i = 0; i < mesh.vertexCount; i++)
            {
                Vector3 *vertex = (Vector3 *)&mesh.vertices[i * 3];
                float height = CURVE_AMPLITUDE * sinf(CURVE_FREQUENCY * (vertex->x + xOffset + vertex->z + zOffset));
                vertex->y = height;
                // float xPosition = vertex->x + xOffset;
                // float zPosition = vertex->y + zOffset;
                // vertex->y += CURVE_AMPLITUDE * sinf(CURVE_FREQUENCY * (xPosition, zPosition));
            }

            grounds[x][z].model = LoadModelFromMesh(mesh);
            grounds[x][z].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grassTexture;
            grounds[x][z].position = Vector3{xOffset, 0.0f, zOffset};
        }
    }
};

// Ends the drawing loop and draws some other things outside of the main game
void EndDrawingLoop()
{
    EndBlendMode();
    EndMode3D();
    DrawText(TextFormat("FPS: %i", GetFPS()), screenWidth - 220, screenHeight - 100, 30, GREEN);

    uiManager.DrawShakeTreePrompt(true, 250.0f);

    EndDrawing();
}

bool PressedExit()
{
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE);
}

void InitGameWindowIcon()
{
    Image windowIcon = LoadImage("../src/Assets/Textures/icon.png");
    SetWindowIcon(windowIcon);
};

void InitGame()
{
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Animal Crossing - Dev Build");

    uiManager.LoadUIConfig();

    InitGameWindowIcon();
    SetWindowMonitor(0);
    SetWindowState(FLAG_VSYNC_HINT);
    SetWindowState(FLAG_WINDOW_ALWAYS_RUN);
    SetWindowState(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(30);
    SetExitKey(0);
    characterCamera.InitCamera();
    trees.LoadTrees();
}

void DrawLoop(Vector3 characterPosition, GroundTile grounds[GRID_SIZE][GRID_SIZE])
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(characterCamera.camera);
    BeginBlendMode(BLEND_ALPHA);

    flower.DrawFlowerS();

    trees.DrawTrees();

    uiManager.LiveUpdateUI();

    DrawCube(characterPosition, 1.0f, 2.0f, 1.0f, PINK);

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

void UnloadEverything(GroundTile grounds[GRID_SIZE][GRID_SIZE])
{
    UnloadModel(flower.flowerModel);
    UnloadModel(ground);
    trees.UnloadTrees();

    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int z = 0; z < GRID_SIZE; z++)
        {
            UnloadModel(grounds[x][z].model);
        }
    }

    CloseWindow();
}

int main(void)
{
    InitGame();
    Grass grass;
    Texture2D grassTexture = grass.grassTexture;

    flower.LoadFLowers();
    flower.GenerateRandomFlowers(25, 50.0f, 50.0f);

    GroundTile grounds[GRID_SIZE][GRID_SIZE];
    GenerateCurvedGround(grounds, grassTexture);

    while (!WindowShouldClose())
    {

        gameControls.UpdateControls(&characterPosition, characterSpeed);
        characterCamera.UpdateCamera(&characterPosition);
        DrawLoop(characterPosition, grounds);

        if (PressedExit())
        {
            break;
        }
    }

    UnloadEverything(grounds);
    return 0;
}
