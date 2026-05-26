#include "PlayerFacingSystem.h"
#include "../../utils/collision/EntityColAABB.h"
#include "../../utils/collision/EntityColCenter.h"

void playerFacingSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    SDL_FPoint center = entityColCenter(entityColAABB(p.base, 0));

    const SDL_FPoint cameraOff = ctx.data.camera.offset;
    float mouseWorldX = ctx.mouse.x - cameraOff.x;

    if (mouseWorldX < center.x)
        p.base.facing.facing[0] = FacingDirection::Left;
    else if (mouseWorldX > center.x)
        p.base.facing.facing[0] = FacingDirection::Right;
}
