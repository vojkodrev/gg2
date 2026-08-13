#include "DestroyEffectSystem.h"
#include "../../../structs/animation/AnimationState.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "EffectFree.h"
#include <cstdint>

void destroyEffectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count[0]; i++)
    {
        if (!ctx.data.effect.pool.active[0][i])
            continue;

        if (ctx.data.effect.destroyType[i] == DestroyEffectType::None)
        {
            continue;
        }
        else if (ctx.data.effect.destroyType[i] == DestroyEffectType::AnimationEnd)
        {
            if (ctx.data.effect.base.animation.animationState[i] != AnimationState::Finished)
                continue;

            effectFree(ctx.data.effect, ctx.data.groups, i);
        }
        else if (ctx.data.effect.destroyType[i] == DestroyEffectType::Timer)
        {
            if (ctx.data.effect.destroyTimer[i] > 0.0f)
                continue;

            effectFree(ctx.data.effect, ctx.data.groups, i);
        }
    }
}
