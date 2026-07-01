#include "AutoAttackTimerSystem.h"

void autoAttackTimerSystem(Context &ctx)
{
    auto &attackTimer = ctx.data.player.autoAttack.attackTimer;
    if (attackTimer > 0.0f)
    {
        attackTimer -= ctx.frame.dt;
        if (attackTimer < 0.0f)
            attackTimer = 0.0f;
    }
}
