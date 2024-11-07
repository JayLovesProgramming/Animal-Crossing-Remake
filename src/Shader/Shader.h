#pragma once

#include "raylib.h"

class ShaderManager
{
public:
    inline static Shader skyBoxShader;
    inline static int viewEyeLoc;
    inline static int viewCenterLoc;
    inline static int runTimeLoc;
    inline static int resolutionLoc;
    inline static float runTime;

    inline static int resolution[2];

    inline static void InitializeSkyboxLighting();
    inline static void UpdateSkyboxLighting();
};
