#include "CancelCastBarSystem.h"
#include "../../../structs/ui/CastType.h"

void cancelCastBarSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    if (!player.base.position.dirty[0])
        return;

    auto &castBar = player.castbar;
    castBar.type[0] = CastType::None;
    castBar.timer[0] = 0.0f;
    castBar.duration[0] = 0.0f;
    castBar.hideTimer[0] = 0.0f;
    castBar.progressBar.show[0] = false;
    castBar.progressBar.dirty[0] = true;
}
