#include "SpriteAnimationSystem.h"
#include "AdvanceSpriteAnimation.h"

void spriteAnimationSystem(Context &ctx)
{
    uint64_t now = ctx.frame.now;

    advanceSpriteAnimation(ctx.data.player.base.animation, 0, now);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        advanceSpriteAnimation(ctx.data.npc.base.animation, i, now);
    }

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        advanceSpriteAnimation(ctx.data.object.base.animation, i, now);

    for (uint32_t i = 0; i < MAX_EFFECTS; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        advanceSpriteAnimation(ctx.data.effect.base.animation, i, now);
    }
}
