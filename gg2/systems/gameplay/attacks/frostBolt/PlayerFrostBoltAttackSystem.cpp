#include "PlayerFrostBoltAttackSystem.h"
#include "../../../structs/core/constants/FrostBoltConstants.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../structs/ui/CastType.h"

void playerFrostBoltAttackSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    const auto &weapon = player.equipment.weapon;
    if (!ctx.data.action.digit3Released ||
        player.globalCooldownTimer > 0.0f ||
        player.castbar.timer[0] > 0.0f ||
        player.selectedNpc == INVALID_ID ||
        !weapon.exists[0] ||
        weapon.type[0] != WeaponType::Magic)
        return;

    player.castbar.type[0] = CastType::FrostBolt;
    player.castbar.timer[0] = FROST_BOLT_CAST_TIME;
    player.castbar.duration[0] = FROST_BOLT_CAST_TIME;
    player.castbar.hideTimer[0] = 0.0f;
    player.castbar.progressBar.dirty[0] = true;
}
