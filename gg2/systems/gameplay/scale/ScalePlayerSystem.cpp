#include "ScalePlayerSystem.h"
#include "ScaleAnimationFrames.h"
#include "ScaleEntityBasePosition.h"

void scalePlayerSystem(Context &ctx)
{
    scaleEntityBasePosition(ctx.data.player.base, 0);
    scaleAnimationFrames(ctx.data.player.base.animation, ctx.data.player.base.scale, 1);
}
