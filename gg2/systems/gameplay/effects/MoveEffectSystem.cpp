#include "MoveEffectSystem.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/EffectType.h"
#include "../npc/select/PlaceNpcSelector.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"
#include <cstdint>

void moveEffectSystem(Context &ctx)
{
    if (ctx.data.player.selectedEffectId != -1 && ctx.data.player.selectedNpc != -1)
    {
        const int effectIndex = ctx.data.player.selectedEffectId;
        const int npcIndex = ctx.data.player.selectedNpc;

        if (ctx.data.npc.base.position.dirty[npcIndex])
            placeNpcSelector(ctx, effectIndex, npcIndex);
    }

    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        if (ctx.data.effect.type[i] == EffectType::Projectile)
        {
            const int npcIndex = ctx.data.effect.target.id[i];
            moveEntityColCenterToward(
                ctx,
                ctx.data.effect.base,
                i,
                entityColCenter(entityColAABB(ctx.data.npc.base, npcIndex)),
                PROJECTILE_SPEED);
        }
    }
}
