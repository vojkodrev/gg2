#include "FlipPlayerSystem.h"
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateEntityFlip.h"

void flipPlayerSystem(Context &ctx)
{
    updateEntityFlip(ctx.data.player.base.facing, 0);
    updateEntityAnchorAndCollisionFlip(ctx.data.player.base, 0);
}
