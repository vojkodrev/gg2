#include "ScalePlayerSystem.h"
#include "ScaleAnimationFrames.h"

void scalePlayerSystem(Context &ctx)
{
    ctx.data.player.position.w[0] = ctx.data.player.position.initialW[0] * ctx.data.player.scale[0];
    ctx.data.player.position.h[0] = ctx.data.player.position.initialH[0] * ctx.data.player.scale[0];
    scaleAnimationFrames(ctx.data.player.animation, ctx.data.player.scale, 1);
}
