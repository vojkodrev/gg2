#include "ScalePlayerSystem.h"
#include "ScaleEntityBase.h"

void scalePlayerSystem(Context &ctx)
{
    scaleEntityBase(ctx.data.player.base, 0);
}
