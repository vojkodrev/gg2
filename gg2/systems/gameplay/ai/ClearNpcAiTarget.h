#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/constants/IndexConstants.h"

inline void clearNpcAiTarget(uint32_t n, Context &ctx)
{
    ctx.data.npc.ai.target.type[n] = EntityType::None;
    ctx.data.npc.ai.target.id[n] = INVALID_ID;
}
