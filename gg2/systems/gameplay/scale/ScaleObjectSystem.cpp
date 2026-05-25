#include "ScaleObjectSystem.h"
#include "ScaleAnimationFrames.h"
#include "ScaleEntityBasePosition.h"
#include <cstdint>

void scaleObjectSystem(Context &ctx)
{
    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        scaleEntityBasePosition(ctx.data.object.base, i);
    scaleAnimationFrames(ctx.data.object.base.animation, ctx.data.object.base.scale, ctx.data.object.objectCount);
}
