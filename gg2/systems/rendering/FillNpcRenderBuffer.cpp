#include "FillNpcRenderBuffer.h"
#include "FillWeaponRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillNpcRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < npc.npcCount; i++)
    {
        int f = npc.base.animation.frameIndex[i];
        uint32_t n = rb.count++;
        rb.src.x[n] = (float)npc.base.animation.frame.src.x[i][f];
        rb.src.y[n] = (float)npc.base.animation.frame.src.y[i][f];
        rb.src.w[n] = (float)npc.base.animation.frame.src.w[i][f];
        rb.src.h[n] = (float)npc.base.animation.frame.src.h[i][f];
        rb.src.rotate[n] = 0.0f;
        rb.dst.x[n] = npc.base.position.x[i];
        rb.dst.y[n] = npc.base.position.y[i];
        rb.dst.w[n] = npc.base.position.w[i];
        rb.dst.h[n] = npc.base.position.h[i];
        rb.dst.sortY[n] = rb.dst.y[n] + npc.base.animation.frame.collision.offY[i][f];
        uint32_t groupId = rb.groupCount++;
        rb.group.id[n] = groupId;
        rb.group.zIndex[n] = PARENT_Z_INDEX;
        rb.flipX[n] = npc.base.facing.flipX[i];

        fillWeaponRenderBuffer(rb, npc.equipment.weapon, i, n, groupId);
    }
}
