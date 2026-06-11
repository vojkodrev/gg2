#include "EquipmentDepthSystem.h"
#include "SyncEntityBaseDepthYFromParent.h"
#include <cstdint>

void equipmentDepthSystem(Context &ctx)
{
    syncEntityBaseDepthYFromParent(
        ctx.data.player.equipment.weapon.base,
        ctx.data.player.base,
        0);
    syncEntityBaseDepthYFromParent(
        ctx.data.player.equipment.ammo.base,
        ctx.data.player.base,
        0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        syncEntityBaseDepthYFromParent(
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base,
            i);
        syncEntityBaseDepthYFromParent(
            ctx.data.npc.equipment.ammo.base,
            ctx.data.npc.base,
            i);
    }
}
