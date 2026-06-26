#include "MouseWorldStateSystem.h"

void mouseWorldStateSystem(Context &ctx)
{
    ctx.mouse.worldX = ctx.mouse.x - ctx.data.camera.offset.x;
    ctx.mouse.worldY = ctx.mouse.y - ctx.data.camera.offset.y;
}
