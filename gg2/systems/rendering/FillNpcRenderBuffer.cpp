#include "FillNpcRenderBuffer.h"

void FillNpcRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        uint32_t n = rb.count++;
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
}
