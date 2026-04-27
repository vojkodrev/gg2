#pragma once
#include <atomic>
#include <cstdint>
#include "Constants.h"
#include "NPCPatrolPoint.h"
#include "NPCPath.h"
#include "NPCPathStatus.h"
#include "NPCSpawn.h"
#include "NPCAiState.h"
#include "NPCAiType.h"

struct NPCAi
{
    NPCAiType type[MAX_NPCS];

    NPCAiState state[MAX_NPCS];
    
    NPCSpawn spawn;

    NPCPatrolPoint patrol;
    uint32_t       patrolCount[MAX_NPCS];
    uint32_t       patrolIndex[MAX_NPCS];

    NPCPath       path;
    uint32_t      pathLength[MAX_NPCS];
    uint32_t      pathIndex[MAX_NPCS];
    std::atomic<NPCPathStatus> pathStatus[MAX_NPCS];

    float idleTimer[MAX_NPCS];
};
