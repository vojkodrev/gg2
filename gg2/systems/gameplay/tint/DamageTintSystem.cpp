#include "DamageTintSystem.h"
#include "../../../structs/core/constants/TintConstants.h"
#include <cstdint>

void damageTintSystem(Context &ctx)
{
    const auto &playerHealth = ctx.data.player.statistics.health;
    if (playerHealth.dirty[0] && playerHealth.hp[0] < playerHealth.prevHp[0])
    {
        ctx.data.player.base.tint.damageTimer[0] = DAMAGE_TINT_CLEAR_TIME;
        ctx.data.player.equipment.weapon.base.tint.damageTimer[0] = DAMAGE_TINT_CLEAR_TIME;
        ctx.data.player.equipment.ammo.base.tint.damageTimer[0] = DAMAGE_TINT_CLEAR_TIME;
    }

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        const auto &npcHealth = ctx.data.npc.statistics.health;
        const bool isPoisoned = ctx.data.npc.serpentStingDebuffTimer[i] > 0.0f;
        const bool isSlowed = ctx.data.npc.concussiveShotDebuffTimer[i] > 0.0f;
        if (npcHealth.dirty[i] && npcHealth.hp[i] < npcHealth.prevHp[i])
        {
            ctx.data.npc.base.tint.damageTimer[i] = DAMAGE_TINT_CLEAR_TIME;
            ctx.data.npc.equipment.weapon.base.tint.damageTimer[i] = DAMAGE_TINT_CLEAR_TIME;
            ctx.data.npc.equipment.ammo.base.tint.damageTimer[i] = DAMAGE_TINT_CLEAR_TIME;
        }
        ctx.data.npc.base.tint.isPoisoned[i] = isPoisoned;
        ctx.data.npc.equipment.weapon.base.tint.isPoisoned[i] = isPoisoned;
        ctx.data.npc.equipment.ammo.base.tint.isPoisoned[i] = isPoisoned;
        ctx.data.npc.base.tint.isSlowed[i] = isSlowed;
        ctx.data.npc.equipment.weapon.base.tint.isSlowed[i] = isSlowed;
        ctx.data.npc.equipment.ammo.base.tint.isSlowed[i] = isSlowed;
    }
}
