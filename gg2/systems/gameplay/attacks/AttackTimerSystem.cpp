#include "AttackTimerSystem.h"

void attackTimerSystem(Context &ctx)
{
    auto &autoAttack = ctx.data.player.autoAttack;
    auto &attackTimer = autoAttack.attackTimer;
    auto &globalCooldownTimer = ctx.data.player.globalCooldownTimer;

    if (attackTimer > 0.0f)
    {
        attackTimer -= ctx.frame.dt;
        if (attackTimer < 0.0f)
            attackTimer = 0.0f;
    }

    if (globalCooldownTimer > 0.0f)
    {
        globalCooldownTimer -= ctx.frame.dt;
        if (globalCooldownTimer < 0.0f)
            globalCooldownTimer = 0.0f;
    }
}
