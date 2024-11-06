// Controls/Controls.h
#pragma once

#include <cmath>
#include "raylib.h"
#include "Camera/Camera.h"
#include "Map/Ground/Ground.h"
#include "Map/Tree/Tree.h"

using std::cout, std::endl;

class GameControls
{
public:
    inline static bool nearTree;

    static void UpdateControls(Vector3 *characterPos, float characterSpeed);

private:
    inline static int animFrameCounter = 0;
};
