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

#include "Window.h"
#include "Camera.h"
#include "Flower.h"
#include "Grass.h"
#include "Tree.h"
#include "Controls.h"
#include "UI.h"
#include "Debug.h"
#include "Character.h"
#include "Map.h"
#include "Mouse.h"

Vector3 characterPosition = {0.0f, 1.0f, 0.0f};
GroundTile grounds[GRID_SIZE][GRID_SIZE];
