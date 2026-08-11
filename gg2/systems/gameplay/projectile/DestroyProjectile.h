#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/core/EntityType.h"
#include "../effects/EffectFree.h"
#include <cstdint>

inline void destroyProjectile(Context &ctx, uint32_t effectIndex)
{
    const int parentId = ctx.data.effect.parent.id[effectIndex];

    switch (ctx.data.effect.parent.type[effectIndex])
    {
        case EntityType::Player:
            ctx.data.player.equipment.weapon.ranged.showAmmo[parentId] = true;
            break;
        case EntityType::NPC:
            if (ctx.data.npc.active[parentId])
                ctx.data.npc.equipment.weapon.ranged.showAmmo[parentId] = true;
            break;
        default:
            break;
    }

    effectFree(ctx.data.effect, ctx.data.groups, effectIndex);
}
