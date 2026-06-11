#include "EffectDepthSystem.h"
#include "SyncEntityBaseDepthYFromParent.h"
#include <cstdint>

void effectDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        syncEntityBaseDepthYFromParent(
            ctx.data.effect.base,
            ctx.data.player.base,
            i,
            0);
    }
}
