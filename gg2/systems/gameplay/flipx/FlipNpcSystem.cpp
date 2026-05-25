#include "FlipNpcSystem.h"
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateEntityFlip.h"
#include <cstdint>

void flipNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityFlip(ctx.data.npc.base.facing, i);
        updateEntityAnchorAndCollisionFlip(ctx.data.npc.base, i);
    }
}
