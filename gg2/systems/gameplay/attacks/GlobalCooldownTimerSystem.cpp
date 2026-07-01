#include "GlobalCooldownTimerSystem.h"

void globalCooldownTimerSystem(Context &ctx)
{
    auto &globalCooldownTimer = ctx.data.player.globalCooldownTimer;
    if (globalCooldownTimer > 0.0f)
    {
        globalCooldownTimer -= ctx.frame.dt;
        if (globalCooldownTimer < 0.0f)
            globalCooldownTimer = 0.0f;
    }
}
