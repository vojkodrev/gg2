#include "SetMagicActionBarIconsTint.h"
#include "SetActionBarIconTint.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"

void setMagicActionBarIconsTint(Context &ctx)
{
    const int frostNovaIndex = ctx.data.actionBar.frostNovaIndex;
    if (frostNovaIndex == INVALID_ID)
        return;

    auto &tint = ctx.data.actionBar.icon.base.tint;
    const bool onCooldown =
        ctx.data.player.globalCooldownTimer > 0.0f ||
        ctx.data.player.frostNovaCooldownTimer > 0.0f;
    setActionBarIconTint(
        tint,
        frostNovaIndex,
        onCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R : CLEAR_TINT_R,
        onCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G : CLEAR_TINT_G,
        onCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B : CLEAR_TINT_B,
        onCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A : CLEAR_TINT_A);
}
