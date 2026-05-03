#include "FillPlayerRenderBuffer.h"

void fillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &player = ctx.data.player;
    int f = player.animation.frameIndex[0];
    uint32_t n = rb.count++;
    rb.src.x[n] = (float)player.animation.frame.src.x[0][f];
    rb.src.y[n] = (float)player.animation.frame.src.y[0][f];
    rb.src.w[n] = (float)player.animation.frame.src.w[0][f];
    rb.src.h[n] = (float)player.animation.frame.src.h[0][f];
    rb.dst.x[n] = player.position.x[0];
    rb.dst.y[n] = player.position.y[0];
    rb.dst.w[n] = player.position.w[0];
    rb.dst.h[n] = player.position.h[0];
    rb.dst.colOffY[n] = player.animation.frame.collision.offY[0][f];
    rb.flipX[n] = player.facing.facing[0] != player.facing.initialFacing[0];
}
