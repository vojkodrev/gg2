#include "FillRenderBufferSystem.h"
#include <SDL3/SDL.h>
#include "FillPlayerRenderBuffer.h"
#include "FillNpcRenderBuffer.h"
#include "FillObjectRenderBuffer.h"
#include "SortRenderBuffer.h"
#include "../gameplay/camera/GetCameraOffset.h"

void fillRenderBufferSystem(Context &ctx)
{
    ctx.renderBuffer.count = 0;
    fillPlayerRenderBuffer(ctx);
    fillNpcRenderBuffer(ctx);
    fillObjectRenderBuffer(ctx);
    sortRenderBuffer(ctx);

    SDL_FPoint off = getCameraOffset(ctx);
    auto &rb = ctx.renderBuffer;
    for (uint32_t i = 0; i < rb.count; i++)
    {
        rb.dst.x[i] += off.x;
        rb.dst.y[i] += off.y;
    }
}
