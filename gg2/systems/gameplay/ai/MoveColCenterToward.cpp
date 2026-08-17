#include "MoveColCenterToward.h"
#include "NpcConstants.h"
#include "../facing/SetFacingTowardX.h"
#include "../../../utils/entity/MoveEntityColCenterToward.h"

void moveNpcColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed)
{
    auto &npc = ctx.data.npc;
    const SDL_FRect col = mainEntityColAABB(npc.base, n);
    const SDL_FPoint colCenter = entityColCenter(col);

    moveNpcColCenterToward(
        ctx,
        n,
        colCenter,
        target,
        speed);
}

void moveNpcColCenterToward(
    Context &ctx,
    uint32_t n,
    const SDL_FPoint &colCenter,
    SDL_FPoint target,
    float speed)
{
    auto &npc = ctx.data.npc;

    moveEntityColCenterToward(
        ctx,
        npc.base,
        n,
        colCenter,
        target,
        speed);

    if (npc.ai.flipTimer[n] > 0.0f)
        return;

    const bool facingChanged = setFacingTowardX(
        npc.base.facing,
        n,
        colCenter.x,
        target.x);
    if (facingChanged)
        npc.ai.flipTimer[n] = NPC_FLIP_COOLDOWN_TIME;
}
