#include "FlipNpcSystem.h"
#include "SyncEntityFlipAndMirrorOffsets.h"
#include <cstdint>

void flipNpcSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.npc.pool.count; i++)
    {
        if (!ctx.data.npc.pool.active[i])
            continue;

        if (!ctx.data.npc.base.facing.dirty[i])
            continue;

        syncEntityFlipAndMirrorOffsets(ctx.data.npc.base, i);
    }
}
