#include "SetMagicActionBarIconsTint.h"
#include "SetActionBarIconTint.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"

void setMagicActionBarIconsTint(Context &ctx)
{
    auto &actionBar = ctx.data.actionBar;
    const int frostNovaIndex = actionBar.frostNovaIndex;
    if (frostNovaIndex == INVALID_ID)
        return;

    auto &tint = actionBar.icon.base.tint;
    const bool onGlobalCooldown = ctx.data.player.globalCooldownTimer > 0.0f;
    const bool frostNovaOnCooldown = onGlobalCooldown ||
        ctx.data.player.frostNovaCooldownTimer > 0.0f;
    setActionBarIconTint(
        tint,
        frostNovaIndex,
        frostNovaOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R : CLEAR_TINT_R,
        frostNovaOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G : CLEAR_TINT_G,
        frostNovaOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B : CLEAR_TINT_B,
        frostNovaOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A : CLEAR_TINT_A);

    setActionBarIconTint(
        tint,
        actionBar.arcaneExplosionIndex,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R : CLEAR_TINT_R,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G : CLEAR_TINT_G,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B : CLEAR_TINT_B,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A : CLEAR_TINT_A);
}
