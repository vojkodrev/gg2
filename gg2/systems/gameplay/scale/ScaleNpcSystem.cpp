#include "ScaleNpcSystem.h"
#include "ScaleAnimationFrames.h"
#include "ScaleEntityBasePosition.h"
#include <cstdint>

void scaleNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        scaleEntityBasePosition(ctx.data.npc.base, i);
    scaleAnimationFrames(ctx.data.npc.base.animation, ctx.data.npc.base.scale, ctx.data.npc.npcCount);
}
