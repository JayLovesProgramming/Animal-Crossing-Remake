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
                vertex->y += CURVE_AMPLITUDE * sinf(CURVE_FREQUENCY * (vertex->x, vertex->z));
            }

            grounds[x][z].model = LoadModelFromMesh(mesh);
            grounds[x][z].model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = grassTexture;
            grounds[x][z].position = Vector3{ xOffset, 0.0f, zOffset };
        }
    }
};

void EndDrawingLoop()
{
    EndBlendMode();
    EndMode3D();
    DrawText(TextFormat("FPS: %i", GetFPS()), screenWidth - 220, screenHeight - 100, 30, GREEN);
    EndDrawing();
}

// void LoadFencesTexture()
// {
//     fenceTexture = LoadTexture("../src/Assets/Textures/fence.png");
//     assert(fenceTexture.id != 0);
// }

// void DrawFences()
// {
//     for (int i = 0; i < fenceAmount; i++)
//     {
//         // DrawCube(Vector3{i* 1.5f, 0.5f, 0.0f}, 1.0f, 1.0f, 0.2f, WHITE);
//         // DrawBillboard(characterCamera.camera, fenceTexture, Vector3{i* 1.5f, 0.5f, 0.0f}, 1.0f, WHITE);
//         // DrawTexture(fenceTexture, (i * 1.0), 0.0f, WHITE);
//         Rectangle fenceRectangle = {1.0f, 1.0f, 2.0f, 2.0f};
//         Vector2 fenceVec2 = {1.0f, 2.0f};
//         DrawTextureRec(fenceTexture, fenceRectangle, fenceVec2, RED);
//     }
// }

bool PressedExit()
{
    return IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_BACKSPACE);
}


void InitGame()
{
    InitWindow(screenWidth, screenHeight, "Animal Crossing Remake By Jay");
    SetWindowMonitor(0);
    SetWindowState(FLAG_VSYNC_HINT);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(30);
    SetExitKey(0);
    characterCamera.InitCamera();
    trees.LoadTrees();
    // LoadFencesTexture();
}

void DrawLoop(Vector3 characterPosition, GroundTile grounds[GRID_SIZE][GRID_SIZE])
{
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode3D(characterCamera.camera);
    BeginBlendMode(BLEND_ALPHA);
    
    flower.DrawFlowerS();
    
    trees.DrawTrees();

    DrawCube(characterPosition, 1.0f, 2.0f, 1.0f, PINK);

    // DrawFences();

    for(int x = 0; x < GRID_SIZE; x++) {
        for(int z = 0; z < GRID_SIZE; z++) {
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
    UnloadTexture(grassTexture);
    trees.UnloadTrees();

    for(int x = 0; x < GRID_SIZE; x++) {
        for(int z = 0; z < GRID_SIZE; z++) {
            UnloadModel(grounds[x][z].model);
        }
    }
    
    CloseWindow();
}


int main(void)
{
    InitGame();

    Vector3 characterPosition = {0.0f, 1.0f, 0.0f};
    Grass grass;
    grass.LoadGrassTexture();
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
