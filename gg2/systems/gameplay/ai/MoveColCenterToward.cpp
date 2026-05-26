#include "MoveColCenterToward.h"
#include "EntityBaseColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include <cmath>

void moveColCenterToward(Context &ctx, uint32_t n, SDL_FPoint target, float speed)
{
    auto &npc = ctx.data.npc;
    float dt = ctx.frame.dt;
    SDL_FRect col = entityBaseColAABB(npc.base, n);
    SDL_FPoint colCenter = entityColCenter(col);
    float dx = target.x - colCenter.x;
    float dy = target.y - colCenter.y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;
    npc.base.position.x[n] += dx / d * speed * dt;
    npc.base.position.y[n] += dy / d * speed * dt;
    if (dx < 0.0f)
        npc.base.facing.facing[n] = FacingDirection::Left;
    else if (dx > 0.0f)
        npc.base.facing.facing[n] = FacingDirection::Right;
}
