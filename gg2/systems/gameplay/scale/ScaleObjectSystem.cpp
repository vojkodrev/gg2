#include "ScaleObjectSystem.h"
#include "ScaleAnimationFrames.h"
#include <cstdint>

void scaleObjectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
    {
        ctx.data.object.position.w[i] = ctx.data.object.position.initialW[i] * ctx.data.object.scale[i];
        ctx.data.object.position.h[i] = ctx.data.object.position.initialH[i] * ctx.data.object.scale[i];
    }
    scaleAnimationFrames(ctx.data.object.animation, ctx.data.object.scale, ctx.data.object.objectCount);
}
