#include "DestroyNpcSelectorSystem.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../effects/EffectFree.h"

void destroyNpcSelectorSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    if (player.selectedEffectId == INVALID_ID)
        return;

    if (player.previousSelectedNpc == player.selectedNpc)
        return;

    effectFree(ctx.data.effect, ctx.data.groups, player.selectedEffectId);
    player.selectedEffectId = INVALID_ID;
}
