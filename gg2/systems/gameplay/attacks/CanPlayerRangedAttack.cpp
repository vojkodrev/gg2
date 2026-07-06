#include "CanPlayerRangedAttack.h"
#include "../../../structs/core/constants/PlayerConstants.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../../utils/collision/DistToEntity.h"

bool canPlayerRangedAttack(Context &ctx)
{
    const int npcIndex = ctx.data.player.selectedNpc;
    if (npcIndex == -1)
        return false;
    if (!ctx.data.npc.active[npcIndex])
        return false;
    if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
        return false;

    const auto &playerWeapon = ctx.data.player.equipment.weapon;
    if (playerWeapon.type[0] != WeaponType::Ranged)
        return false;

    if (distToEntity(ctx, npcIndex, EntityType::Player, 0) <
        PLAYER_RANGED_ATTACK_MIN_DISTANCE)
        return false;

    return true;
}
