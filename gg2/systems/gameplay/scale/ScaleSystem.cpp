#include "ScaleSystem.h"
#include <cstdint>

void scaleSystem(Context &ctx)
{
    ctx.data.player.position.w[0] = ctx.data.player.position.initialW[0] * ctx.data.player.scale[0];
    ctx.data.player.position.h[0] = ctx.data.player.position.initialH[0] * ctx.data.player.scale[0];

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        ctx.data.npc.position.w[i] = ctx.data.npc.position.initialW[i] * ctx.data.npc.scale[i];
        ctx.data.npc.position.h[i] = ctx.data.npc.position.initialH[i] * ctx.data.npc.scale[i];
    }

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
    {
        ctx.data.object.position.w[i] = ctx.data.object.position.initialW[i] * ctx.data.object.scale[i];
        ctx.data.object.position.h[i] = ctx.data.object.position.initialH[i] * ctx.data.object.scale[i];
    }
}
