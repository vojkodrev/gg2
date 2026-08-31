#include "CancelPlayerCastSystem.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/ui/CastType.h"
#include "../../effects/EffectFree.h"

void cancelPlayerCastSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    if (!player.base.position.inputMovement[0])
        return;

    auto &castingEffectId =
        player.equipment.weapon.magic.castingEffectId[0];
    if (castingEffectId != INVALID_ID)
    {
        effectFree(
            ctx.data.effect,
            ctx.data.groups,
            castingEffectId);
        castingEffectId = INVALID_ID;
    }

    auto &castBar = player.castbar;
    castBar.type[0] = CastType::None;
    castBar.timer[0] = 0.0f;
    castBar.duration[0] = 0.0f;
    castBar.hideTimer[0] = 0.0f;
    castBar.progressBar.show[0] = false;
    castBar.progressBar.dirty[0] = true;
}
