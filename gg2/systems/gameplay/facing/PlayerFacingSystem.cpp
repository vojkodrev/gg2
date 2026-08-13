#include "PlayerFacingSystem.h"
#include "SetFacingTowardX.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/rect/EntityPositionCenter.h"

void playerFacingSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    const SDL_FPoint center = entityPositionCenter(p.base.position, 0);
    float facingTargetX = ctx.mouse.worldX;

    const int selectedNpc = p.selectedNpc;
    if (selectedNpc != INVALID_ID && ctx.data.npc.active[selectedNpc])
        facingTargetX = entityColCenter(entityColAABB(ctx.data.npc.base, selectedNpc)).x;

    setFacingTowardX(p.base.facing, 0, center.x, facingTargetX);
}
