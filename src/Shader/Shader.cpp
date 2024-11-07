#include "Shader.h"
#include "Window/Window.h"
#include "Camera/Camera.h"

void ShaderManager::InitializeSkyboxLighting()
{
    // Load raymarching shader
    // NOTE: Defining 0 (NULL) for vertex shader forces usage of internal default vertex shader
    skyBoxShader = LoadShader(0, TextFormat("C:/Users/jayxw/Desktop/AnimalCrossing/src/Shader/raymarching.fs"));

    // Get shader locations for required uniforms
    viewEyeLoc = GetShaderLocation(skyBoxShader, "viewEye");
    viewCenterLoc = GetShaderLocation(skyBoxShader, "viewCenter");
    runTimeLoc = GetShaderLocation(skyBoxShader, "runTime");
    resolutionLoc = GetShaderLocation(skyBoxShader, "resolution");

    int resolution[2] = {WindowManager::screenWidth, WindowManager::screenHeight};
    SetShaderValue(skyBoxShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);

    runTime = 0.0f;
};

void ShaderManager::UpdateSkyboxLighting()
{
    auto camera = CharacterCamera::camera;
    float cameraPos[3] = {camera.position.x, camera.position.y, camera.position.z};
    float cameraTarget[3] = {camera.target.x, camera.target.y, camera.target.z};
    runTime += GetFrameTime();

    SetShaderValue(skyBoxShader, viewEyeLoc, cameraPos, SHADER_UNIFORM_VEC3);
    SetShaderValue(skyBoxShader, viewCenterLoc, cameraTarget, SHADER_UNIFORM_VEC3);
    SetShaderValue(skyBoxShader, runTimeLoc, &runTime, SHADER_UNIFORM_FLOAT);

    if (IsWindowResized())
    {
        resolution[0] = (float)GetScreenWidth();
        resolution[1] = (float)GetScreenHeight();
        SetShaderValue(skyBoxShader, resolutionLoc, resolution, SHADER_UNIFORM_VEC2);
    }
};
