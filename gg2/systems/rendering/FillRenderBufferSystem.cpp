#include "FillRenderBufferSystem.h"
#include "RenderBufferOps.h"
#include <SDL3/SDL.h>
#include "Constants.h"
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
    SDL_FRect screen = {0, 0, ctx.data.camera.position.w[0], ctx.data.camera.position.h[0]};
    auto &rb = ctx.renderBuffer;
    uint32_t visible = 0;
    for (uint32_t i = 0; i < rb.count; i++)
    {
        SDL_FRect dst = {rb.dst.x[i] + off.x, rb.dst.y[i] + off.y, rb.dst.w[i], rb.dst.h[i]};
        if (!SDL_HasRectIntersectionFloat(&dst, &screen))
            continue;
        copyRenderEntry(rb, visible++, i, &dst);
    }
    rb.count = visible;
}
