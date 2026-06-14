#include "EffectDepthSystem.h"
#include "../../../structs/effect/ParentType.h"
#include <cstdint>

void effectDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count; i++)
    {
        if (!ctx.data.effect.pool.active[i])
            continue;

        switch (ctx.data.effect.parent.type[i])
        {
            case ParentType::Player:
                ctx.data.effect.base.depthY[i] =
                    ctx.data.player.base.depthY[ctx.data.effect.parent.id[i]];
                break;
            case ParentType::NPC:
                ctx.data.effect.base.depthY[i] =
                    ctx.data.npc.base.depthY[ctx.data.effect.parent.id[i]];
                break;
        }
    }
}
