#pragma once
#include "Context.h"
#include "RenderBufferOps.h"
#include <SDL3/SDL.h>

inline void compactVisibleRenderEntries(Context &ctx)
{
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
    auto &rb = ctx.renderBuffer;
    uint32_t visible = 0;
    for (uint32_t i = 0; i < rb.count; i++)
    {
        SDL_FRect dst = {
            rb.dst.absolute[i] ? rb.dst.x[i] : rb.dst.x[i] + off.x,
            rb.dst.absolute[i] ? rb.dst.y[i] : rb.dst.y[i] + off.y,
            rb.dst.w[i],
            rb.dst.h[i]
        };
        if (!SDL_HasRectIntersectionFloat(&dst, &screen))
            continue;
        copyRenderEntry(rb, visible++, i, &dst);
    }
    rb.count = visible;
}
