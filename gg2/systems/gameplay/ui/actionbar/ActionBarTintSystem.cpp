#include "ActionBarTintSystem.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/SerpentStingConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"

void actionBarTintSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    auto &actionBar = ctx.data.actionBar;

    actionBar.rangedAutoAttack.base.tint.r[0] =
        player.autoAttack.active ? AUTO_ATTACK_ACTION_BAR_TINT_R : CLEAR_TINT_R;
    actionBar.rangedAutoAttack.base.tint.g[0] =
        player.autoAttack.active ? AUTO_ATTACK_ACTION_BAR_TINT_G : CLEAR_TINT_G;
    actionBar.rangedAutoAttack.base.tint.b[0] =
        player.autoAttack.active ? AUTO_ATTACK_ACTION_BAR_TINT_B : CLEAR_TINT_B;
    actionBar.rangedAutoAttack.base.tint.a[0] =
        player.autoAttack.active ? AUTO_ATTACK_ACTION_BAR_TINT_A : CLEAR_TINT_A;

    const bool onGlobalCooldown = player.globalCooldownTimer > 0.0f;
    const bool hasEnoughManaForSerpentSting =
        player.statistics.mana.mana[0] >= SERPENT_STING_MANA_COST;
    actionBar.serpentSting.base.tint.r[0] =
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_R : NO_MANA_TINT_R;
    actionBar.serpentSting.base.tint.g[0] =
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_G : NO_MANA_TINT_G;
    actionBar.serpentSting.base.tint.b[0] =
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_B : NO_MANA_TINT_B;
    actionBar.serpentSting.base.tint.a[0] =
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_A : NO_MANA_TINT_A;
}
