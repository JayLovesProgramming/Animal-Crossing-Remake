#include "Character.h"

#include "raylib.h"
#include "rlgl.h"
#include "Map/Ground/Ground.h"
#include "Controls/Mouse.h"
#include <iostream>
#include <cassert>

using std::cout, std::endl;

void Character::LoadCharacterModel()
{

    model = LoadModel(modelPath); // Load the character model
    assert(model.meshCount > 0);  // Assert the character model to prevent any crashing further down the line

    Matrix rotation = MatrixRotateY(PI); // The model by default is not rotated correctly, hard coded for now..
    model.transform = rotation;          // The model by default is not rotated correctly, hard coded for now..

    modelAnimations = LoadModelAnimations(modelPath, &animsCount); // Load the models animations and assign the count of anims to animsCount
};

void Character::CharacterWalk(bool isWalking)
{
    assert(modelAnimations);

    animIndex = 2;
    if (isWalking)
    {
        animIndex = 6;
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
        float movementAngle = atan2f(newPosition.z - initialPosition.z, newPosition.x - initialPosition.x);

        Matrix rotation = MatrixRotateY(movementAngle);
        model.transform = rotation;

        CharacterWalk(true);
    }
    else
    {
        // Play idle animation
        CharacterWalk(false);
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

    // cout << "Characer Rotation X: " << rotX << endl;
    // cout << "Characer Rotation Z: " << rotZ << endl;

    rlRotatef(rotX, 1.0f, 0.0f, 0.0f);
    rlRotatef(rotZ, 0.0f, 0.0f, -1.0f);

    DrawModel(model, Vector3{0.0f, 0.0f, 0.0f}, 0.5f, WHITE);
    // DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 2.0f, 1.0f, LIME);

    rlPopMatrix();
};
