#include "FillPlayerRenderBuffer.h"
#include "../../structs/core/constants/RenderConstants.h"

void fillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &player = ctx.data.player;
    uint32_t groupId = rb.groupCount++;

    int f = player.animation.frameIndex[0];
    uint32_t n = rb.count++;
    rb.src.x[n] = (float)player.animation.frame.src.x[0][f];
    rb.src.y[n] = (float)player.animation.frame.src.y[0][f];
    rb.src.w[n] = (float)player.animation.frame.src.w[0][f];
    rb.src.h[n] = (float)player.animation.frame.src.h[0][f];
    rb.src.angle[n] = (float)player.animation.frame.src.angle[0][f];
    rb.dst.x[n] = player.position.x[0];
    rb.dst.y[n] = player.position.y[0];
    rb.dst.w[n] = player.position.w[0];
    rb.dst.h[n] = player.position.h[0];
    rb.dst.sortY[n] = rb.dst.y[n] + player.animation.frame.collision.offY[0][f];
    rb.group.id[n] = groupId;
    rb.group.zIndex[n] = PARENT_Z_INDEX;
    rb.flipX[n] = player.facing.facing[0] != player.facing.initialFacing[0];

    auto &weapon = player.equipment.weapon;
    auto &weaponPos = player.equipment.position;
    if (weapon.frameCount[0] > 0)
    {
        int wf = weapon.frameIndex[0];
        uint32_t wn = rb.count++;
        rb.src.x[wn] = (float)weapon.frame.src.x[0][wf];
        rb.src.y[wn] = (float)weapon.frame.src.y[0][wf];
        rb.src.w[wn] = (float)weapon.frame.src.w[0][wf];
        rb.src.h[wn] = (float)weapon.frame.src.h[0][wf];
        rb.dst.x[wn] = player.position.x[0] + weaponPos.x[0];
        rb.dst.y[wn] = player.position.y[0] + weaponPos.y[0];
        rb.dst.w[wn] = weaponPos.w[0];
        rb.dst.h[wn] = weaponPos.h[0];
        rb.dst.sortY[wn] = rb.dst.sortY[n];
        rb.group.id[wn] = groupId;
        rb.group.zIndex[wn] = WEAPON_Z_INDEX;
        rb.flipX[wn] = rb.flipX[n];
        rb.src.angle[wn] = rb.flipX[wn] ? (float)weapon.frame.src.angleFlipped[0][wf] : (float)weapon.frame.src.angle[0][wf];
    }
}
