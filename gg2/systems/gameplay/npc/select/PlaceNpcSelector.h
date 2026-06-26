#pragma once
#include "Context.h"

inline void placeNpcSelector(Context &ctx, int effectIndex, int npcIndex)
{
    ctx.data.effect.base.position.x[effectIndex] =
        ctx.data.npc.base.position.x[npcIndex] +
        (ctx.data.npc.base.position.w[npcIndex] - ctx.data.effect.base.position.w[effectIndex]) * 0.5f;
    ctx.data.effect.base.position.y[effectIndex] =
        ctx.data.npc.base.position.y[npcIndex] -
        (ctx.data.effect.base.position.h[effectIndex] - ctx.data.npc.base.position.h[npcIndex]) * 0.5f;
    ctx.data.effect.base.position.dirty[effectIndex] = true;
}
