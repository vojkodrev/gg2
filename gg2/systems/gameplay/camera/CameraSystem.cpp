#include "CameraSystem.h"

void cameraSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    auto &cam = ctx.data.camera;
    cam.position.x[0] = p.base.position.x[0] + p.base.position.w[0] * 0.5f;
    cam.position.y[0] = p.base.position.y[0] + p.base.position.h[0] * 0.5f;
    cam.offset = {
        cam.position.w[0] * 0.5f - cam.position.x[0],
        cam.position.h[0] * 0.5f - cam.position.y[0]
    };
    cam.screen = {0.0f, 0.0f, cam.position.w[0], cam.position.h[0]};
}
