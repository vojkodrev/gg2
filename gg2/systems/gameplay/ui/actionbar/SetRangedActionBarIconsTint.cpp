#include "SetRangedActionBarIconsTint.h"
#include "SetActionBarIconTint.h"
#include "../../../../structs/core/constants/AttackConstants.h"
#include "../../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/core/constants/SerpentStingConstants.h"
#include "../../../../structs/core/constants/TauntConstants.h"
#include "../../../../structs/core/constants/TintConstants.h"

void setRangedActionBarIconsTint(Context &ctx)
{
    auto &player = ctx.data.player;
    auto &actionBar = ctx.data.actionBar;
    if (actionBar.rangedAutoAttackIndex == INVALID_ID)
        return;

    auto &tint = actionBar.icon.base.tint;

    const bool autoAttackActive = player.autoAttack.active[0];
    setActionBarIconTint(
        tint,
        actionBar.rangedAutoAttackIndex,
        autoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_R : CLEAR_TINT_R,
        autoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_G : CLEAR_TINT_G,
        autoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_B : CLEAR_TINT_B,
        autoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_A : CLEAR_TINT_A);

    const int petId = player.petId;
    const bool petAutoAttackActive =
        petId != INVALID_ID && ctx.data.npc.autoAttack.active[petId];
    setActionBarIconTint(
        tint,
        actionBar.petAutoAttackIndex,
        petAutoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_R : CLEAR_TINT_R,
        petAutoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_G : CLEAR_TINT_G,
        petAutoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_B : CLEAR_TINT_B,
        petAutoAttackActive ? AUTO_ATTACK_ACTION_BAR_TINT_A : CLEAR_TINT_A);

    const bool petTauntOnCooldown =
        petId != INVALID_ID && ctx.data.npc.tauntTimer[petId] > 0.0f;
    const bool hasEnoughManaForPetTaunt =
        petId == INVALID_ID ||
        ctx.data.npc.statistics.mana.mana[petId] >= TAUNT_MANA_COST;
    setActionBarIconTint(
        tint,
        actionBar.petTauntIndex,
        petTauntOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R :
        hasEnoughManaForPetTaunt ? CLEAR_TINT_R : NO_MANA_TINT_R,
        petTauntOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G :
        hasEnoughManaForPetTaunt ? CLEAR_TINT_G : NO_MANA_TINT_G,
        petTauntOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B :
        hasEnoughManaForPetTaunt ? CLEAR_TINT_B : NO_MANA_TINT_B,
        petTauntOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A :
        hasEnoughManaForPetTaunt ? CLEAR_TINT_A : NO_MANA_TINT_A);

    const bool onGlobalCooldown = player.globalCooldownTimer > 0.0f;
    const bool hasEnoughManaForSerpentSting =
        player.statistics.mana.mana[0] >= SERPENT_STING_MANA_COST;
    setActionBarIconTint(
        tint,
        actionBar.serpentStingIndex,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_R : NO_MANA_TINT_R,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_G : NO_MANA_TINT_G,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_B : NO_MANA_TINT_B,
        onGlobalCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A :
        hasEnoughManaForSerpentSting ? CLEAR_TINT_A : NO_MANA_TINT_A);

    const bool concussiveShotOnCooldown =
        onGlobalCooldown || player.concussiveShotCooldownTimer > 0.0f;
    const bool hasEnoughManaForConcussiveShot =
        player.statistics.mana.mana[0] >= CONCUSSIVE_SHOT_MANA_COST;
    setActionBarIconTint(
        tint,
        actionBar.concussiveShotIndex,
        concussiveShotOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_R :
        hasEnoughManaForConcussiveShot ? CLEAR_TINT_R : NO_MANA_TINT_R,
        concussiveShotOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_G :
        hasEnoughManaForConcussiveShot ? CLEAR_TINT_G : NO_MANA_TINT_G,
        concussiveShotOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_B :
        hasEnoughManaForConcussiveShot ? CLEAR_TINT_B : NO_MANA_TINT_B,
        concussiveShotOnCooldown ? GLOBAL_COOLDOWN_ACTION_BAR_TINT_A :
        hasEnoughManaForConcussiveShot ? CLEAR_TINT_A : NO_MANA_TINT_A);
}
