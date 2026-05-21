#include "ScaleNpcSystem.h"
#include "ScaleAnimationFrames.h"
#include <cstdint>

void scaleNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        ctx.data.npc.position.w[i] = ctx.data.npc.position.initialW[i] * ctx.data.npc.scale[i];
        ctx.data.npc.position.h[i] = ctx.data.npc.position.initialH[i] * ctx.data.npc.scale[i];
    }
    scaleAnimationFrames(ctx.data.npc.animation, ctx.data.npc.scale, ctx.data.npc.npcCount);
}
