#include "FlipPlayerSystem.h"
#include "SyncEntityFlipAndMirrorOffsets.h"

void flipPlayerSystem(Context &ctx)
{
    if (!ctx.data.player.base.facing.dirty[0])
        return;

    syncEntityFlipAndMirrorOffsets(ctx.data.player.base, 0);
}
