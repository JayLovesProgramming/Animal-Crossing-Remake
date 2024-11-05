#include "Character.h"

void Character::HandleCharacterMovement()
{
    float groundHeight = Map::GetHeightAtPosition(characterPosition.x, characterPosition.z);
    characterPosition.y = groundHeight + 0.5f;

    float mapRotation = Map::CalculateRotationForObject(characterPosition.x, characterPosition.z);

    rlPushMatrix();
    rlTranslatef(characterPosition.x, characterPosition.y, characterPosition.z);
    rlRotatef(mapRotation * (180.0f / PI), -1.0f, 0.0f, 0.0f); 

    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 1.0f, 1.0f, 1.0f, RAYWHITE);
    
    rlPopMatrix();
}
