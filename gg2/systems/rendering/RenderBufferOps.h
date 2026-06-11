#pragma once
#include "../../structs/render/RenderBuffer.h"
#include <SDL3/SDL.h>

inline void swapRenderEntry(RenderBuffer &rb, int a, int b)
{
    std::swap(rb.src.x[a], rb.src.x[b]);
    std::swap(rb.src.y[a], rb.src.y[b]);
    std::swap(rb.src.w[a], rb.src.w[b]);
    std::swap(rb.src.h[a], rb.src.h[b]);
    std::swap(rb.src.rotate[a], rb.src.rotate[b]);
    std::swap(rb.rotationCenter.point.x[a], rb.rotationCenter.point.x[b]);
    std::swap(rb.rotationCenter.point.y[a], rb.rotationCenter.point.y[b]);
    std::swap(rb.rotationCenter.hasCenter[a], rb.rotationCenter.hasCenter[b]);
    std::swap(rb.dst.x[a], rb.dst.x[b]);
    std::swap(rb.dst.y[a], rb.dst.y[b]);
    std::swap(rb.dst.w[a], rb.dst.w[b]);
    std::swap(rb.dst.h[a], rb.dst.h[b]);
    std::swap(rb.dst.depthY[a], rb.dst.depthY[b]);
    std::swap(rb.group.id[a], rb.group.id[b]);
    std::swap(rb.group.zIndex[a], rb.group.zIndex[b]);
    std::swap(rb.flipX[a], rb.flipX[b]);
}

inline void copyRenderEntry(RenderBuffer &rb, int dst, int src, const SDL_FRect *dstOverride = nullptr)
{
    rb.src.x[dst] = rb.src.x[src];
    rb.src.y[dst] = rb.src.y[src];
    rb.src.w[dst] = rb.src.w[src];
    rb.src.h[dst] = rb.src.h[src];
    rb.src.rotate[dst] = rb.src.rotate[src];
    rb.rotationCenter.point.x[dst] = rb.rotationCenter.point.x[src];
    rb.rotationCenter.point.y[dst] = rb.rotationCenter.point.y[src];
    rb.rotationCenter.hasCenter[dst] = rb.rotationCenter.hasCenter[src];
    rb.dst.x[dst] = dstOverride ? dstOverride->x : rb.dst.x[src];
    rb.dst.y[dst] = dstOverride ? dstOverride->y : rb.dst.y[src];
    rb.dst.w[dst] = dstOverride ? dstOverride->w : rb.dst.w[src];
    rb.dst.h[dst] = dstOverride ? dstOverride->h : rb.dst.h[src];
    rb.dst.depthY[dst] = rb.dst.depthY[src];
    rb.group.id[dst] = rb.group.id[src];
    rb.group.zIndex[dst] = rb.group.zIndex[src];
    rb.flipX[dst] = rb.flipX[src];
}
