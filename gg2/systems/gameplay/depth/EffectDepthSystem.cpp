#include "EffectDepthSystem.h"
#include "../../../structs/core/constants/ActionBarConstants.h"
#include "../../../structs/core/constants/WindowConstants.h"
#include "../../../structs/entity/EntityType.h"
#include <cstdint>

void effectDepthSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.effect.pool.count[0]; i++)
    {
        if (!ctx.data.effect.pool.active[0][i])
            continue;

        switch (ctx.data.effect.parent.type[i])
        {
            case EntityType::Player:
                ctx.data.effect.base.depthY[i] =
                    ctx.data.player.base.depthY[ctx.data.effect.parent.id[i]];
                break;
            case EntityType::NPC:
                ctx.data.effect.base.depthY[i] =
                    ctx.data.npc.base.depthY[ctx.data.effect.parent.id[i]];
                break;
            case EntityType::ActionBarIcon:
                ctx.data.effect.base.depthY[i] =
                    ctx.data.actionBar.icon.base.depthY[
                        ctx.data.effect.parent.id[i]];
                break;
            case EntityType::Window:
                ctx.data.effect.base.depthY[i] = WINDOW_DEPTH_Y;
                break;
            default:
                break;
        }
    }
}
