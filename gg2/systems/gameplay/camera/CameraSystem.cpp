#include "CameraSystem.h"

void cameraSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    auto &cam = ctx.data.camera;
    cam.position.x[0] = p.position.x[0] + p.position.w[0] * 0.5f;
    cam.position.y[0] = p.position.y[0] + p.position.h[0] * 0.5f;
}
