#include "FlipPlayerSystem.h"
#include "UpdateEntityAnchorCollisionFlip.h"

void flipPlayerSystem(Context &ctx)
{
    if (!ctx.data.player.base.facing.dirty[0])
        return;

    updateEntityAnchorCollisionFlip(ctx.data.player.base, 0);
}
