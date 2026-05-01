#include "CameraSystem.h"

void cameraSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    auto &cam = ctx.data.camera;
    cam.x = p.x + p.w * 0.5f;
    cam.y = p.y + p.h * 0.5f;
}
