#pragma once
#include "NpcConstants.h"
#include "AStarConstants.h"

struct NPCPathPoint
{
    int x[MAX_NPCS][ASTAR_MAX_PATH];
    int y[MAX_NPCS][ASTAR_MAX_PATH];
};
