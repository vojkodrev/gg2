#include "MoveColCenterToward.h"
#include "NpcConstants.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"

void moveNpcColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed)
{
    auto &npc = ctx.data.npc;
    const SDL_FRect col = entityColAABB(npc.base, n);
    const SDL_FPoint colCenter = entityColCenter(col);
    const float dx = target.x - colCenter.x;

    moveEntityColCenterToward(ctx, npc.base, n, target, speed);

    if (npc.ai.flipTimer[n] > 0.0f)
        return;

    FacingDirection facing = npc.base.facing.facing[n];
    if (dx < 0.0f)
        facing = FacingDirection::Left;
    else if (dx > 0.0f)
        facing = FacingDirection::Right;

    const bool facingChanged = npc.base.facing.facing[n] != facing;
    npc.base.facing.dirty[n] = facingChanged;
    npc.base.facing.facing[n] = facing;
    if (facingChanged)
        npc.ai.flipTimer[n] = NPC_FLIP_COOLDOWN_TIME;
}
