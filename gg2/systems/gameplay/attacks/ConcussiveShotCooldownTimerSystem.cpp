#include "ConcussiveShotCooldownTimerSystem.h"

void concussiveShotCooldownTimerSystem(Context &ctx)
{
    auto &concussiveShotCooldownTimer = ctx.data.player.concussiveShotCooldownTimer;
    if (concussiveShotCooldownTimer > 0.0f)
    {
        concussiveShotCooldownTimer -= ctx.frame.dt;
        if (concussiveShotCooldownTimer < 0.0f)
            concussiveShotCooldownTimer = 0.0f;
    }
}
