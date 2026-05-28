#include "FlipNpcSystem.h"
#include "UpdateEntityAnchorCollisionFlip.h"
#include <cstdint>

void flipNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
        updateEntityAnchorCollisionFlip(ctx.data.npc.base, i);
}
