#include "FillNpcRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillNpcRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        int f = npc.animation.frameIndex[i];
        uint32_t n = rb.count++;
        rb.src.x[n] = (float)npc.animation.frame.src.x[i][f];
        rb.src.y[n] = (float)npc.animation.frame.src.y[i][f];
        rb.src.w[n] = (float)npc.animation.frame.src.w[i][f];
        rb.src.h[n] = (float)npc.animation.frame.src.h[i][f];
        rb.src.angle[n] = (float)npc.animation.frame.src.angle[i][f];
        rb.dst.x[n] = npc.position.x[i];
        rb.dst.y[n] = npc.position.y[i];
        rb.dst.w[n] = npc.position.w[i];
        rb.dst.h[n] = npc.position.h[i];
        rb.dst.sortY[n] = rb.dst.y[n] + npc.animation.frame.collision.offY[i][f];
        rb.group.id[n] = rb.groupCount++;
        rb.group.zIndex[n] = PARENT_Z_INDEX;
        rb.flipX[n] = npc.facing.facing[i] != npc.facing.initialFacing[i];
    }
}
