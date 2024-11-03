// Controls/Controls.h
#pragma once

#include <cmath>
#include "raylib.h"
#include "Camera/Camera.h"
#include "Map/Map.h"
#include "Tree/Tree.h"

class GameControls
{
public:
    static void UpdateControls(Vector3 *characterPosition, float characterSpeed);

private:
    static int animFrameCounter;
};

int GameControls::animFrameCounter = 0;
