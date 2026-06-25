#include "DestroyEffectByTimerSystem.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "EffectFree.h"
#include <cstdint>

void destroyEffectByTimerSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;

    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        if (ctx.data.effect.destroyType[i] != DestroyEffectType::Timer)
            continue;

        ctx.data.effect.destroyTimer[i] -= dt;
        if (ctx.data.effect.destroyTimer[i] > 0.0f)
            continue;

        ctx.data.effect.destroyTimer[i] = 0.0f;
        effectFree(ctx.data.effect, ctx.data.groups, i);
    }
}
