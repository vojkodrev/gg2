#include "PlayerFacingSystem.h"
#include "camera/GetCameraOffset.h"
#include "../../utils/collision/EntityColAABBPlayer.h"
#include "../../utils/collision/EntityColCenter.h"

void playerFacingSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    SDL_FPoint center = entityColCenter(entityColAABB(p));

    SDL_FPoint cameraOff = getCameraOffset(ctx);
    float mouseWorldX = ctx.mouse.x - cameraOff.x;

    if (mouseWorldX < center.x)
        p.facing.facing[0] = FacingDirection::Left;
    else if (mouseWorldX > center.x)
        p.facing.facing[0] = FacingDirection::Right;
}
