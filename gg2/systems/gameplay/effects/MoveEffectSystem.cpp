#include "MoveEffectSystem.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/effect/EffectType.h"
#include "../npc/select/PlaceNpcSelector.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"
#include <cstdint>

void moveEffectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        if (ctx.data.effect.type[i] == EffectType::Projectile)
        {
            moveEntityColCenterToward(
                ctx,
                ctx.data.effect.base,
                i,
                ctx.data.effect.target,
                i,
                PROJECTILE_SPEED);
        }
        else if (ctx.data.effect.type[i] == EffectType::Selector)
        {
            const int npcIndex = ctx.data.effect.parent.id[i];
            if (ctx.data.npc.base.position.dirty[npcIndex])
                placeNpcSelector(ctx, (int)i, npcIndex);
        }
    }
}
