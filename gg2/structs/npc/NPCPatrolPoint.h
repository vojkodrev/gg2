#pragma once
#include <cstdint>
#include "constants.h"

struct NPCPatrolPoint
{
    float x[MAX_NPCS][MAX_PATROL_POINTS];
    float y[MAX_NPCS][MAX_PATROL_POINTS];
};
