#pragma once
#include "Context.h"
#include <cstdint>

inline void resetNpcFollowPath(Context &ctx, uint32_t n)
{
    ctx.data.npc.ai.path.status[n].store(
        NPCPathStatus::IDLE,
        std::memory_order_relaxed);
}
