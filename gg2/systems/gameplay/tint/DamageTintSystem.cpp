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
    const auto &playerConcussiveShotDebuff =
        ctx.data.player.concussiveShotDebuff;
    bool playerIsSlowed = false;
    for (uint32_t debuffIndex = 0;
         debuffIndex < MAX_DEBUFF_SLOTS;
        debuffIndex++)
        playerIsSlowed = playerIsSlowed ||
            playerConcussiveShotDebuff.pool.active[0][debuffIndex];
    ctx.data.player.base.tint.isSlowed[0] = playerIsSlowed;
    ctx.data.player.equipment.weapon.base.tint.isSlowed[0] = playerIsSlowed;
    ctx.data.player.equipment.ammo.base.tint.isSlowed[0] = playerIsSlowed;

    for (uint32_t npcId = 0; npcId < MAX_NPCS; npcId++)
    {
        if (!ctx.data.npc.active[npcId])
            continue;

        const auto &npcHealth = ctx.data.npc.statistics.health;
        const auto &serpentStingDebuff = ctx.data.npc.serpentStingDebuff;
        const auto &concussiveShotDebuff = ctx.data.npc.concussiveShotDebuff;
        const auto &frostNovaDebuff = ctx.data.npc.frostNovaDebuff;
        bool isPoisoned = false;
        bool isSlowed = false;
        for (uint32_t debuffIndex = 0; debuffIndex < MAX_DEBUFF_SLOTS; debuffIndex++)
        {
            isPoisoned = isPoisoned || serpentStingDebuff.pool.active[npcId][debuffIndex];
            isSlowed = isSlowed ||
                concussiveShotDebuff.pool.active[npcId][debuffIndex] ||
                frostNovaDebuff.pool.active[npcId][debuffIndex];
        }
        if (npcHealth.dirty[npcId] && npcHealth.hp[npcId] < npcHealth.prevHp[npcId])
        {
            ctx.data.npc.base.tint.damageTimer[npcId] = DAMAGE_TINT_CLEAR_TIME;
            ctx.data.npc.equipment.weapon.base.tint.damageTimer[npcId] = DAMAGE_TINT_CLEAR_TIME;
            ctx.data.npc.equipment.ammo.base.tint.damageTimer[npcId] = DAMAGE_TINT_CLEAR_TIME;
        }
        ctx.data.npc.base.tint.isPoisoned[npcId] = isPoisoned;
        ctx.data.npc.equipment.weapon.base.tint.isPoisoned[npcId] = isPoisoned;
        ctx.data.npc.equipment.ammo.base.tint.isPoisoned[npcId] = isPoisoned;
        ctx.data.npc.base.tint.isSlowed[npcId] = isSlowed;
        ctx.data.npc.equipment.weapon.base.tint.isSlowed[npcId] = isSlowed;
        ctx.data.npc.equipment.ammo.base.tint.isSlowed[npcId] = isSlowed;
    }
}
