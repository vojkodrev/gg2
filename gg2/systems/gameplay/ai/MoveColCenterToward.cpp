#include "MoveColCenterToward.h"
#include "EntityAABB.h"
#include <cmath>

void MoveColCenterToward(Context &ctx, uint32_t n, float tx, float ty, float speed)
{
    auto &npc = ctx.data.npc;
    float dt = ctx.frame.dt;
    SDL_FRect col = EntityColAABB(npc, n);
    SDL_FPoint colCenter = EntityColCenter(col);
    float dx = tx - colCenter.x;
    float dy = ty - colCenter.y;
    float d = sqrtf(dx * dx + dy * dy);
    if (d == 0.0f)
        return;
    npc.position.x[n] += dx / d * speed * dt;
    npc.position.y[n] += dy / d * speed * dt;
}
