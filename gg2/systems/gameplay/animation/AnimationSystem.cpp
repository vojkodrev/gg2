#include "AnimationSystem.h"
#include "AdvanceAnimation.h"

void animationSystem(Context &ctx)
{
    uint64_t now = ctx.frame.now;

    advanceAnimation(ctx.data.player.base.animation, 1u, now);
    advanceAnimation(
        ctx.data.npc.base.animation,
        ctx.data.npc.pool.count,
        now,
        ctx.data.npc.pool.active);
    advanceAnimation(ctx.data.object.base.animation, ctx.data.object.objectCount, now);
}
