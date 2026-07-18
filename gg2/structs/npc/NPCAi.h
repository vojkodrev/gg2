#pragma once
#include <cstdint>
#include "NpcConstants.h"
#include "NPCPatrol.h"
#include "NPCPath.h"
#include "NPCSpawn.h"
#include "NPCAiState.h"
#include "NPCAiType.h"
#include "../core/EntityReference.h"

struct NPCAi
{
    NPCAiType type[MAX_NPCS];

    NPCAiState state[MAX_NPCS];
    EntityReference<MAX_NPCS> target;

    NPCSpawn spawn;

    NPCPatrol patrol;

    NPCPath path;

    float attackedTimer[MAX_NPCS];
    float idleTimer[MAX_NPCS];
    float repathTimer[MAX_NPCS];
    float pathTargetCheckTimer[MAX_NPCS];
    float targetRangeCheckTimer[MAX_NPCS];
    float flipTimer[MAX_NPCS];
};
