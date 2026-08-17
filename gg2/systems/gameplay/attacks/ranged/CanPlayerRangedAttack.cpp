#include "CanPlayerRangedAttack.h"
#include "IsRangedAttackTargetTooClose.h"
#include "IsRangedTargetVisible.h"
#include "../../../utils/collision/MainEntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include "../../../utils/collision/GetEntityColAABB.h"
#include "../../../structs/core/constants/AttackConstants.h"
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
    if (!playerWeapon.exists[0] ||
        playerWeapon.type[0] != WeaponType::Ranged)
        return false;

    if (isRangedAttackTargetTooClose(
            ctx,
            npcIndex,
            EntityType::Player,
            0))
        return false;

    auto &player = ctx.data.player;
    if (player.targetVisibleTimer <= 0.0f)
    {
        player.targetVisibleTimer = RANGED_TARGET_VISIBLE_CHECK_TIME;
        player.targetVisible = isRangedTargetVisible(
            ctx,
            player.equipment,
            player.base,
            0,
            getEntityColAABB(ctx, EntityType::NPC, npcIndex),
            entityColCenter(mainEntityColAABB(player.base, 0)));
    }
    if (!player.targetVisible)
        return false;

    return true;
}
