// Character/Character.cpp
#include "Character.h"

void Character::HandleCharacterMovement(Vector3 &characterPosition)
{
    float groundHeight = SurfaceManager::GetHeightAtPosition(characterPosition.x, characterPosition.z);

    characterPosition.y = (groundHeight + .5f);

    DrawCubeV(characterPosition, Vector3{1.0f, 1.0f, 1.0f}, RED); // Draw a pink cube for the character. TODO: Replace with actual Model
};
