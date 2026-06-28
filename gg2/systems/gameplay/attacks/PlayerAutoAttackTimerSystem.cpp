#include "PlayerAutoAttackTimerSystem.h"

void playerAutoAttackTimerSystem(Context &ctx)
{
    auto &attackTimer = ctx.data.player.autoAttack.attackTimer;
    if (attackTimer <= 0.0f)
        return;

    attackTimer -= ctx.frame.dt;
    if (attackTimer < 0.0f)
        attackTimer = 0.0f;
}
