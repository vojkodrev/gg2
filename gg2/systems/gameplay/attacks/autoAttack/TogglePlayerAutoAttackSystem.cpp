#include "TogglePlayerAutoAttackSystem.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/equipment/WeaponType.h"

void togglePlayerAutoAttackSystem(Context &ctx)
{
    if (!ctx.data.action.digit1Released)
        return;

    const auto &weapon = ctx.data.player.equipment.weapon;
    if (!weapon.exists[0] ||
        (weapon.type[0] != WeaponType::Melee &&
         weapon.type[0] != WeaponType::Ranged))
        return;

    auto &autoAttack = ctx.data.player.autoAttack;
    const int npcIndex = ctx.data.player.selectedNpc;
    if (!autoAttack.active[0] && npcIndex == INVALID_ID)
        return;

    autoAttack.active[0] = !autoAttack.active[0];
}
