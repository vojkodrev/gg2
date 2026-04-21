#pragma once
#include <cstdint>
#include "constants.h"
#include "NPCPatrolPoint.h"
#include "NPCSpawn.h"

struct NPCAi
{
    char type[MAX_NPCS][MAX_AI_TYPE_LEN];
    NPCSpawn spawn;
    NPCPatrolPoint patrol;
    uint32_t patrolCount[MAX_NPCS];
    uint32_t patrolIndex[MAX_NPCS];
};
