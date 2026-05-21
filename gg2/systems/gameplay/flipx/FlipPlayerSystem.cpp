#include "FlipPlayerSystem.h"
#include "UpdateEntityAnchorAndCollisionFlip.h"
#include "UpdateEntityFlip.h"

void flipPlayerSystem(Context &ctx)
{
    updateEntityFlip(ctx.data.player.facing, 0);
    updateEntityAnchorAndCollisionFlip(ctx.data.player.animation, 0, ctx.data.player.position.w[0], ctx.data.player.facing.flipX[0]);
}
