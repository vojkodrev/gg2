#include "ScalePlayerLocationSystem.h"
#include "ScaleEntityBaseLocations.h"

void scalePlayerLocationSystem(Context &ctx)
{
    if (!ctx.data.player.base.facing.dirty[0])
        return;

    scaleEntityBaseLocations(ctx.data.player.base, 0);
}
