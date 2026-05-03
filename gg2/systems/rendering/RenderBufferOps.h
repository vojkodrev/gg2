#pragma once
#include "../../structs/render/RenderBuffer.h"
#include <SDL3/SDL.h>

inline void swapRenderEntry(RenderBuffer &rb, int a, int b)
{
    std::swap(rb.src.x[a], rb.src.x[b]);
    std::swap(rb.src.y[a], rb.src.y[b]);
    std::swap(rb.src.w[a], rb.src.w[b]);
    std::swap(rb.src.h[a], rb.src.h[b]);
    std::swap(rb.dst.x[a], rb.dst.x[b]);
    std::swap(rb.dst.y[a], rb.dst.y[b]);
    std::swap(rb.dst.w[a], rb.dst.w[b]);
    std::swap(rb.dst.h[a], rb.dst.h[b]);
    std::swap(rb.dst.colOffY[a], rb.dst.colOffY[b]);
    std::swap(rb.flipX[a], rb.flipX[b]);
}

inline void copyRenderEntry(RenderBuffer &rb, int dst, int src, const SDL_FRect *dstOverride = nullptr)
{
    rb.src.x[dst] = rb.src.x[src];
    rb.src.y[dst] = rb.src.y[src];
    rb.src.w[dst] = rb.src.w[src];
    rb.src.h[dst] = rb.src.h[src];
    rb.dst.x[dst] = dstOverride ? dstOverride->x : rb.dst.x[src];
    rb.dst.y[dst] = dstOverride ? dstOverride->y : rb.dst.y[src];
    rb.dst.w[dst] = dstOverride ? dstOverride->w : rb.dst.w[src];
    rb.dst.h[dst] = dstOverride ? dstOverride->h : rb.dst.h[src];
    rb.dst.colOffY[dst] = rb.dst.colOffY[src];
    rb.flipX[dst] = rb.flipX[src];
}
