#include "PlayerFacingSystem.h"
#include "SetFacingTowardX.h"
#include "../../utils/rect/EntityPositionCenter.h"

void playerFacingSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    SDL_FPoint center = entityPositionCenter(p.base.position, 0);
    setFacingTowardX(p.base.facing, 0, center.x, ctx.mouse.worldX);
}
