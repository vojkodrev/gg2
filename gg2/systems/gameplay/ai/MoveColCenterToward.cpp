#include "MoveColCenterToward.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"

void moveNpcColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed)
{
    auto &npc = ctx.data.npc;
    const SDL_FRect col = entityColAABB(npc.base, n);
    const SDL_FPoint colCenter = entityColCenter(col);
    const float dx = target.x - colCenter.x;

    moveEntityColCenterToward(ctx, npc.base, n, target, speed);

    FacingDirection facing = npc.base.facing.facing[n];
    if (dx < 0.0f)
        facing = FacingDirection::Left;
    else if (dx > 0.0f)
        facing = FacingDirection::Right;

    npc.base.facing.dirty[n] = npc.base.facing.facing[n] != facing;
    npc.base.facing.facing[n] = facing;
}
