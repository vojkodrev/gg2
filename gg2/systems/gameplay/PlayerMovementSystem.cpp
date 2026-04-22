#include "PlayerMovementSystem.h"
#include <cmath>

const float PLAYER_SPEED = 100.0f;

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
    p.x += dx * PLAYER_SPEED * ctx.frame.dt;
    p.y += dy * PLAYER_SPEED * ctx.frame.dt;
}
