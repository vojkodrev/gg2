#include "FlipPlayerSystem.h"
#include "UpdateEntityAnchorCollisionFlip.h"

void flipPlayerSystem(Context &ctx)
{
    updateEntityAnchorCollisionFlip(ctx.data.player.base, 0);
}
