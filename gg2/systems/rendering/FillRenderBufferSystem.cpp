#include "FillRenderBufferSystem.h"
#include "RenderBufferOps.h"
#include <SDL3/SDL.h>
#include "FillPlayerRenderBuffer.h"
#include "FillNpcRenderBuffer.h"
#include "FillObjectRenderBuffer.h"
#include "FillEffectRenderBuffer.h"
#include "SortRenderBuffer.h"

void fillRenderBufferSystem(Context &ctx)
{
    ctx.renderBuffer.count = 0;
    
    fillPlayerRenderBuffer(ctx);
    fillNpcRenderBuffer(ctx);
    fillObjectRenderBuffer(ctx);
    fillEffectRenderBuffer(ctx);

    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
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

    sortRenderBuffer(ctx);
}
