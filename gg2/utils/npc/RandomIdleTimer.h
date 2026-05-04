#pragma once
#include <cstdlib>
#include "NpcMonsterConstants.h"

inline float randomIdleTimer()
{
    return NPC_IDLE_TIME_MIN + (float)rand() / RAND_MAX * (NPC_IDLE_TIME_MAX - NPC_IDLE_TIME_MIN);
}
