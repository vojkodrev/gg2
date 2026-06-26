#include "DestroyNpcSelectorSystem.h"
#include "../../effects/EffectFree.h"

void destroyNpcSelectorSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    if (player.selectedEffectId == -1)
        return;

    if (player.previousSelectedNpc == player.selectedNpc)
        return;

    effectFree(ctx.data.effect, ctx.data.groups, player.selectedEffectId);
    player.selectedEffectId = -1;
}
