#include "Character.h"

// Handles the character movement respective of the maps curvature
void Character::HandleCharacterMovement()
{
    CharacterPosition characterRotatedPos = CalculateCharacterPos();

    rlPushMatrix();
    rlTranslatef(characterPos.x, characterPos.y + characterRotatedPos.groundHeight, characterPos.z);
    rlRotatef(characterRotatedPos.mapRotation * (180.0f / PI), -1.0f, 0.0f, 0.0f); 

    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, RAYWHITE);
    
    rlPopMatrix();
}

// Character Position Relative To Maps Curvature
Character::CharacterPosition Character::CalculateCharacterPos()
{
    float groundHeight = Map::GetHeightAtPosition(Character::characterPos.x, Character::characterPos.z, "character"); // Gets the ground height at any given time, respective to the grounds curvature

    float mapRotation = Map::CalculateRotationForObject(Character::characterPos.x, Character::characterPos.z); // Calculates the map curvature and gives us a valid rotation from it
    
    return { mapRotation, groundHeight };
};
