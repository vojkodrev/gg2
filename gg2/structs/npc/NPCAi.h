#pragma once
#include <cstdint>
#include "constants.h"
#include "NPCPatrolPoint.h"
#include "NPCSpawn.h"
#include "NPCAiState.h"
#include "NPCAiType.h"

struct NPCAi
{
    NPCAiType type[MAX_NPCS];

    NPCSpawn spawn;

    NPCPatrolPoint patrol;
    uint32_t patrolCount[MAX_NPCS];
    uint32_t patrolIndex[MAX_NPCS];

    NPCAiState state[MAX_NPCS];
    float idleTimer[MAX_NPCS];
};
