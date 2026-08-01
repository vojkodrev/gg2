#include "MoveEffectSystem.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/EffectType.h"
#include "../npc/select/PlaceNpcSelector.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/collision/GetEntityColAABB.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"
#include "../../../utils/rect/CenteredRect.h"
#include "../../../utils/rect/EntityPositionCenter.h"
#include <cstdint>

void moveEffectSystem(Context &ctx)
{
    if (ctx.data.player.selectedEffectId != INVALID_ID && ctx.data.player.selectedNpc != INVALID_ID)
    {
        const int effectIndex = ctx.data.player.selectedEffectId;
        const int npcIndex = ctx.data.player.selectedNpc;

        if (ctx.data.npc.base.position.dirty[npcIndex])
            placeNpcSelector(ctx, effectIndex, npcIndex);
    }

    for (uint32_t i = 0; i < ctx.data.effect.pool.count[0]; i++)
    {
        if (!ctx.data.effect.pool.active[0][i])
            continue;

        if (ctx.data.effect.type[i] == EffectType::Projectile)
        {
            moveEntityColCenterToward(
                ctx,
                ctx.data.effect.base,
                i,
                entityColCenter(getEntityColAABB(
                    ctx,
                    ctx.data.effect.target.type[i],
                    ctx.data.effect.target.id[i])),
                PROJECTILE_SPEED);
        }
        else if (
            (ctx.data.effect.type[i] == EffectType::BloodSplatter ||
             ctx.data.effect.type[i] == EffectType::Taunt) &&
            ctx.data.effect.parent.type[i] == EntityType::NPC)
        {
            const int npcIndex = ctx.data.effect.parent.id[i];
            const SDL_FRect effectRect = centeredRect(
                entityPositionCenter(ctx.data.npc.base.position, npcIndex),
                ctx.data.effect.base.position.w[i],
                ctx.data.effect.base.position.h[i]);
            ctx.data.effect.base.position.x[i] = effectRect.x;
            ctx.data.effect.base.position.y[i] = effectRect.y;
            ctx.data.effect.base.position.dirty[i] = true;
        }
    }
}
