#include "FillPlayerRenderBuffer.h"

void fillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
    auto &player = ctx.data.player;
    uint32_t n = rb.count++;
    rb.src.x[n] = (float)player.src.x[0];
    rb.src.y[n] = (float)player.src.y[0];
    rb.src.w[n] = (float)player.src.w[0];
    rb.src.h[n] = (float)player.src.h[0];
    rb.dst.x[n] = player.position.x[0];
    rb.dst.y[n] = player.position.y[0];
    rb.dst.w[n] = player.position.w[0];
    rb.dst.h[n] = player.position.h[0];
    rb.dst.colOffY[n] = player.collision.offY[0];
}
