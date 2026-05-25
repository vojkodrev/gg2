#include "FillPlayerRenderBuffer.h"
#include "equipment/FillEquipmentRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &player = ctx.data.player;
    uint32_t groupId = rb.groupCount++;

    int f = player.base.animation.frameIndex[0];
    uint32_t n = rb.count++;
    rb.src.x[n] = (float)player.base.animation.frame.src.x[0][f];
    rb.src.y[n] = (float)player.base.animation.frame.src.y[0][f];
    rb.src.w[n] = (float)player.base.animation.frame.src.w[0][f];
    rb.src.h[n] = (float)player.base.animation.frame.src.h[0][f];
    rb.src.rotate[n] = 0.0f;
    rb.dst.x[n] = player.base.position.x[0];
    rb.dst.y[n] = player.base.position.y[0];
    rb.dst.w[n] = player.base.position.w[0];
    rb.dst.h[n] = player.base.position.h[0];
    rb.dst.sortY[n] = rb.dst.y[n] + player.base.animation.frame.collision.offY[0][f];
    rb.group.id[n] = groupId;
    rb.group.zIndex[n] = PARENT_Z_INDEX;
    rb.flipX[n] = player.base.facing.flipX[0];

    fillEquipmentRenderBuffer(rb, player.equipment, 0, n, groupId);
}
