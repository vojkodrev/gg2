#include "ScalePlayerLocationSystem.h"
#include "ScaleEntityBaseLocations.h"

void scalePlayerLocationSystem(Context &ctx)
{
    scaleEntityBaseLocations(ctx.data.player.base, 0);
}
