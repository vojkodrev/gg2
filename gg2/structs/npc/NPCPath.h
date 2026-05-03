#pragma once
#include <atomic>
#include <cstdint>
#include "Constants.h"
#include "NPCPathPoint.h"
#include "NPCPathStatus.h"

struct NPCPath
{
    NPCPathPoint point;
    uint32_t length[MAX_NPCS];
    uint32_t index[MAX_NPCS];
    std::atomic<NPCPathStatus> status[MAX_NPCS];
};
