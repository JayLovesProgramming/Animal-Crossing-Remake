#include "Character.h"

#include "raylib.h"
#include "rlgl.h"
#include "Map/Ground/Ground.h"
#include "Controls/Mouse.h"
#include "Controls/Controls.h"
#include "Utils/ConsoleOut.h"
#include <iostream>
#include <cassert>

using std::cout, std::endl;

// Loads the character model, asserts it, rotates it 180 then load the models anims
void Character::LoadCharacterModel()
{
    model = LoadModel(modelPath); // Load the character model
    assert(model.meshCount > 0);  // Assert the character model to prevent any crashing further down the line

    Matrix rotation = MatrixRotateY(PI); // The model by default is not rotated correctly, hard coded for now..
    model.transform = rotation;          // The model by default is not rotated correctly, hard coded for now..

    modelAnimations = LoadModelAnimations(modelPath, &animsCount); // Load the models animations and assign the count of anims to animsCount
};

void Character::UnloadCharacterModel()
{
    // ? Should we unload the model first or the models animations first?
    UnloadModelAnimations(modelAnimations, animsCount);
    UnloadModel(model);
    cout << unloadString << "Character Model" << endl;
};

// Handles ALL character animations here
void Character::CharacterAnimation(bool isWalking)
{
    assert(modelAnimations);

    // ? Is a animation struct a good idea here?

    animIndex = 2; // Idle Animation
    if (isWalking && !GameControls::isJumping)
    {
        animIndex = 6; // Walk/Run Animation
    }
    else if (GameControls::isJumping)
    {
        animIndex = 11; // Jump Animation
    }

    ModelAnimation anim = modelAnimations[animIndex];
    assert(anim.name); // Further assertion to confirm that the model actually holds animations

    if (!printedCurrentAnim)
    {
        cout << "[CURRENT ANIMATION]: " << anim.name << endl;
        printedCurrentAnim = true;
    }

    animCurrentFrame = (animCurrentFrame + 1) % anim.frameCount;
    UpdateModelAnimation(model, anim, animCurrentFrame);
};

void Character::HandleCharacterMovement(Vector3 newPosition, Vector3 initialPosition)
{
    bool characterWalking = (IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D));
    if (characterWalking)
    {
        // Play walk animation
        float movementAngle = atan2f(newPosition.x - initialPosition.x, newPosition.z - initialPosition.z);

        Matrix rotation = MatrixRotateY(movementAngle);
        model.transform = rotation;

        CharacterAnimation(true); // TODO: Use a struct here? Don't pass a bool
    }
    else
    {
        // Play idle animation
        CharacterAnimation(false); // TODO: Use a struct here? Don't pass a bool
    }
};

void Character::DrawCharacter()
{

    float groundHeight = Map::GetHeightAtPosition(characterPos.x, characterPos.z, "character"); // Gets the ground height at any given time, respective to the grounds curvature

    Vector3 normal = Map::GetSurfaceNormalAtPosition(characterPos.x, characterPos.z);

    float rotX = atan2f(normal.z, normal.y) * (180.0f / PI);
    float rotZ = atan2f(normal.x, normal.y) * (180.0f / PI);

    // TODO: Try and avoid using rlPushMatrix, can't we just update the characterPos and use that?
    rlPushMatrix();

    rlTranslatef(characterPos.x, characterPos.y + groundHeight, characterPos.z);

    rlRotatef(rotX, 1.0f, 0.0f, 0.0f);
    rlRotatef(rotZ, 0.0f, 0.0f, -1.0f);

    DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 0.4f, WHITE);
    // DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 2.0f, 1.0f, LIME);

    rlPopMatrix();
};
