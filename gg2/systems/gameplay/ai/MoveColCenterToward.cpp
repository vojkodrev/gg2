#include "MoveColCenterToward.h"
#include "EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include <cmath>

void moveColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed)
{
    auto &npc = ctx.data.npc;
    float dt = ctx.frame.dt;
    SDL_FRect col = entityColAABB(npc.base, n);
    SDL_FPoint colCenter = entityColCenter(col);
    float dx = target.x - colCenter.x;
    float dy = target.y - colCenter.y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;

    npc.base.facing.dirty[n] = false;
    npc.base.position.x[n] += dx / d * speed * dt;
    npc.base.position.y[n] += dy / d * speed * dt;

    FacingDirection facing = npc.base.facing.facing[n];
    if (dx < 0.0f)
        facing = FacingDirection::Left;
    else if (dx > 0.0f)
        facing = FacingDirection::Right;

    npc.base.facing.dirty[n] = npc.base.facing.facing[n] != facing;
    npc.base.facing.facing[n] = facing;
}
