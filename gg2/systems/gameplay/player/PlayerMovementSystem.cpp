#include "PlayerMovementSystem.h"
#include "PlayerConstants.h"
#include "../../../utils/entity/GetEntityMovementSpeed.h"
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

    const float moveSpeed = getEntityMovementSpeed<1>(
        &p.concussiveShotDebuff,
        nullptr,
        0,
        PLAYER_SPEED);
    const float moveX = dx * moveSpeed * ctx.frame.dt;
    const float moveY = dy * moveSpeed * ctx.frame.dt;
    const bool movedByUserInput = moveX != 0.0f || moveY != 0.0f;
    p.base.position.dirty[0] = movedByUserInput;
    p.base.position.inputMovement[0] = movedByUserInput;
    p.base.position.x[0] += moveX;
    p.base.position.y[0] += moveY;
}
