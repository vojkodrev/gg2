#include "CanPlayerRangedAttack.h"
#include "IsRangedAttackTargetTooClose.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../structs/npc/NPCAiType.h"

bool canPlayerRangedAttack(Context &ctx)
{
    const int npcIndex = ctx.data.player.selectedNpc;
    if (npcIndex == INVALID_ID)
        return false;
    if (!ctx.data.npc.active[npcIndex])
        return false;
    if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
        return false;

    const auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.type[0] != WeaponType::Ranged)
        return false;

    if (isRangedAttackTargetTooClose(
            ctx,
            npcIndex,
            EntityType::Player,
            0))
        return false;

    return true;
}
