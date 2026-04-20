#include "FillRenderBufferSystem.h"
#include <functional>
#include <algorithm>

void FillRenderBufferSystem(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    rb.count = 0;

    auto &player = ctx.data.player;
    uint32_t n = rb.count++;
    rb.src.x[n] = (float)player.srcX;
    rb.src.y[n] = (float)player.srcY;
    rb.src.w[n] = (float)player.srcW;
    rb.src.h[n] = (float)player.srcH;
    rb.dst.x[n] = player.x;
    rb.dst.y[n] = player.y;
    rb.dst.w[n] = player.w;
    rb.dst.h[n] = player.h;
    rb.dst.colOffY[n] = player.colOffY;

    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        n = rb.count++;
        rb.src.x[n] = (float)npc.src.x[i];
        rb.src.y[n] = (float)npc.src.y[i];
        rb.src.w[n] = (float)npc.src.w[i];
        rb.src.h[n] = (float)npc.src.h[i];
        rb.dst.x[n] = npc.position.x[i];
        rb.dst.y[n] = npc.position.y[i];
        rb.dst.w[n] = npc.position.w[i];
        rb.dst.h[n] = npc.position.h[i];
        rb.dst.colOffY[n] = npc.collision.offY[i];
    }

    auto &object = ctx.data.object;
    for (uint32_t i = 0; i < object.objectCount; i++)
    {
        n = rb.count++;
        rb.src.x[n] = (float)object.src.x[i];
        rb.src.y[n] = (float)object.src.y[i];
        rb.src.w[n] = (float)object.src.w[i];
        rb.src.h[n] = (float)object.src.h[i];
        rb.dst.x[n] = object.position.x[i];
        rb.dst.y[n] = object.position.y[i];
        rb.dst.w[n] = object.position.w[i];
        rb.dst.h[n] = object.position.h[i];
        rb.dst.colOffY[n] = object.collision.offY[i];
    }

    auto rbSwap = [&](uint32_t a, uint32_t b) {
        std::swap(rb.src.x[a], rb.src.x[b]);
        std::swap(rb.src.y[a], rb.src.y[b]);
        std::swap(rb.src.w[a], rb.src.w[b]);
        std::swap(rb.src.h[a], rb.src.h[b]);
        std::swap(rb.dst.x[a], rb.dst.x[b]);
        std::swap(rb.dst.y[a], rb.dst.y[b]);
        std::swap(rb.dst.w[a], rb.dst.w[b]);
        std::swap(rb.dst.h[a], rb.dst.h[b]);
        std::swap(rb.dst.colOffY[a], rb.dst.colOffY[b]);
    };
    auto depthKey = [&](uint32_t i) { return rb.dst.y[i] + rb.dst.colOffY[i]; };
    std::function<void(int, int)> rbSort = [&](int lo, int hi) {
        if (lo >= hi) return;
        float pivot = depthKey(lo + (hi - lo) / 2);
        int i = lo, j = hi;
        while (i <= j) {
            while (depthKey(i) < pivot) i++;
            while (depthKey(j) > pivot) j--;
            if (i <= j) { rbSwap(i++, j--); }
        }
        rbSort(lo, j);
        rbSort(i, hi);
    };
    if (rb.count > 1)
        rbSort(0, (int)rb.count - 1);
}
