// Main.h
#pragma once

#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath> 
#include <random> 
#include <string> 
#include <sys/stat.h>
#include <assert.h>

#include "Monitor.h"
#include "Camera.h"
#include "Flower.h"
#include "Grass.h"
#include "Tree.h"
#include "Controls.h"
#include "UI.h"
#include "Debug.h"
// #include "DevImGUI.h"

float characterSpeed = 8.15f;

const static auto MAP_SHADER_TYPE = MATERIAL_MAP_DIFFUSE;
const static auto GRID_SIZE = 20;
const static auto GROUND_SIZE = 5.0f;
const static auto CURVE_AMPLITUDE = 15.0f;
const static auto CURVE_FREQUENCY = 0.5f;

// int fenceAmount = 50;

Texture2D grassTexture;
Model ground;
Vector3 characterPosition = {0.0f, 1.0f, 0.0f};
// Texture2D fenceTexture;

struct GroundTile
{
    Model model;
    Vector3 position;
};
