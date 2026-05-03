#include "AnimationSystem.h"
#include "AdvanceAnimation.h"

void animationSystem(Context &ctx)
{
    uint64_t now = ctx.frame.now;

    advanceAnimation(ctx.data.player.animation, 1u, now);
    advanceAnimation(ctx.data.npc.animation, ctx.data.npc.npcCount, now);
    advanceAnimation(ctx.data.object.animation, ctx.data.object.objectCount, now);
}
