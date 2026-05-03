#pragma once
#include "Constants.h"

struct NPCPathPoint
{
    int x[MAX_NPCS][ASTAR_MAX_PATH];
    int y[MAX_NPCS][ASTAR_MAX_PATH];
};
