#include "PlayerMovementSystem.h"
#include "PlayerConstants.h"
#include <cmath>

void playerMovementSystem(Context &ctx)
{
    auto &p = ctx.data.player;
    auto &kb = ctx.keyboard;
    float dx = 0.0f, dy = 0.0f;
    if (kb.w)
        dy -= 1.0f;
    if (kb.s)
        dy += 1.0f;
    if (kb.a)
        dx -= 1.0f;
    if (kb.d)
        dx += 1.0f;
    float len = sqrtf(dx * dx + dy * dy);
    if (len > 0.0f)
    {
        dx /= len;
        dy /= len;
    }
    p.position.x[0] += dx * PLAYER_SPEED * ctx.frame.dt;
    p.position.y[0] += dy * PLAYER_SPEED * ctx.frame.dt;
}
