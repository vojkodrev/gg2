#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/entity/EntityType.h"

inline void setNpcAiTarget(uint32_t n, Context &ctx, EntityType targetType, int targetId)
{
    ctx.data.npc.ai.target.type[n] = targetType;
    ctx.data.npc.ai.target.id[n] = targetId;
}
