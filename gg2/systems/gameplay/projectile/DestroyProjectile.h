#pragma once
#include "../../../structs/core/Context.h"
#include "../../../structs/effect/ParentType.h"
#include "../effects/EffectFree.h"
#include <cstdint>

inline void destroyProjectile(Context &ctx, uint32_t effectIndex)
{
    const int parentId = ctx.data.effect.parent.id[effectIndex];

    switch (ctx.data.effect.parent.type[effectIndex])
    {
        case ParentType::Player:
            ctx.data.player.equipment.weapon.showAmmo[parentId] = true;
            break;
        case ParentType::NPC:
            if (ctx.data.npc.pool.active[parentId])
                ctx.data.npc.equipment.weapon.showAmmo[parentId] = true;
            break;
    }

    effectFree(ctx.data.effect, ctx.data.groups, effectIndex);
}
