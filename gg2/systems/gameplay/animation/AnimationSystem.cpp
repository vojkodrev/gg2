#include "AnimationSystem.h"
#include "AdvanceAnimation.h"

void animationSystem(Context &ctx)
{
    uint64_t now = ctx.frame.now;

    advanceAnimation(ctx.data.player.base.animation, 0, now);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        advanceAnimation(ctx.data.npc.base.animation, i, now);
    }

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        advanceAnimation(ctx.data.object.base.animation, i, now);
}
