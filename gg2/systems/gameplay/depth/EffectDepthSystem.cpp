#include "EffectDepthSystem.h"
#include <cstdint>

void effectDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        ctx.data.effect.base.depthY[i] = ctx.data.player.base.depthY[0];
    }
}
