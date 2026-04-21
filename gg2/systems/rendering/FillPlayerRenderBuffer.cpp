#include "FillPlayerRenderBuffer.h"

void FillPlayerRenderBuffer(Context &ctx)
{
    auto &rb = ctx.renderBuffer;
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
}
