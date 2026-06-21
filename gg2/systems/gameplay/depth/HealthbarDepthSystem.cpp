#include "HealthbarDepthSystem.h"
#include <cstdint>

void healthbarDepthSystem(Context &ctx)
{
    ctx.data.player.healthbar.base.depthY[0] = ctx.data.player.base.depthY[0];

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        ctx.data.npc.healthbar.base.depthY[i] = ctx.data.npc.base.depthY[i];
}
