#include "CastBarTimerSystem.h"
#include "../../../structs/core/constants/CastBarConstants.h"
#include <algorithm>

void castBarTimerSystem(Context &ctx)
{
    const float dt = ctx.frame.dt;
    auto &castBar = ctx.data.player.castbar;
    if (castBar.timer[0] > 0.0f)
    {
        castBar.timer[0] = std::max(0.0f, castBar.timer[0] - dt);
        castBar.progressBar.dirty[0] = true;
        if (castBar.timer[0] == 0.0f)
            castBar.hideTimer[0] = CAST_BAR_HIDE_DELAY;
    }
    else if (castBar.hideTimer[0] > 0.0f)
    {
        castBar.hideTimer[0] =
            std::max(0.0f, castBar.hideTimer[0] - dt);
        if (castBar.hideTimer[0] == 0.0f)
            castBar.progressBar.dirty[0] = true;
    }
}
