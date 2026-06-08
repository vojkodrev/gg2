#pragma once
#include <cstdint>
#include "NpcConstants.h"
#include "NPCPatrol.h"
#include "NPCPath.h"
#include "NPCSpawn.h"
#include "NPCAiState.h"
#include "NPCAiType.h"

struct NPCAi
{
    NPCAiType type[MAX_NPCS];

    NPCAiState state[MAX_NPCS];

    NPCSpawn spawn;

    NPCPatrol patrol;

    NPCPath path;

    float idleTimer[MAX_NPCS];
    float repathTimer[MAX_NPCS];
};
