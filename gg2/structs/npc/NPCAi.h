#pragma once
#include <cstdint>
#include "constants.h"
#include "NPCPatrolPoint.h"

struct NPCAi
{
    char type[MAX_NPCS][MAX_AI_TYPE_LEN];
    NPCPatrolPoint patrol;
    uint32_t patrolCount[MAX_NPCS];
};
