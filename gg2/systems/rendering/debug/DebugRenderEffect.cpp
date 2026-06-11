#include "DebugRenderEffect.h"
#include "DebugRenderEquipmentEntity.h"

void debugRenderEffect(const Context &ctx)
{
    if (!ctx.data.debug.showEffectCollision)
        return;

    const auto &effect = ctx.data.effect;
    for (uint32_t i = 0; i < effect.pool.count; i++)
    {
        if (!effect.pool.active[i])
            continue;

        debugRenderEquipmentEntity(ctx, effect.base, i, SDL_Color{255, 0, 255, 255});
    }
}
