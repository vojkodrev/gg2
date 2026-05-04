#pragma once
#include <cstdint>
#include "CapacityConstants.h"
#include "NPCPatrolPoint.h"

struct NPCPatrol
{
    NPCPatrolPoint point;
    uint32_t count[MAX_NPCS];
    uint32_t index[MAX_NPCS];
};
