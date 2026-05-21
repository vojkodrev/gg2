#include "FlipNpcSystem.h"
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateEntityFlip.h"
#include <cstdint>

void flipNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityFlip(ctx.data.npc.facing, i);
        updateEntityAnchorAndCollisionFlip(ctx.data.npc.animation, i, ctx.data.npc.position.w[i], ctx.data.npc.facing.flipX[i]);
    }
}
