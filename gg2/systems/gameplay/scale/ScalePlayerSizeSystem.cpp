#include "ScalePlayerSizeSystem.h"
#include "ScaleEntityBaseSizes.h"

void scalePlayerSizeSystem(Context &ctx)
{
    scaleEntityBaseSizes(ctx.data.player.base, 0);
}
