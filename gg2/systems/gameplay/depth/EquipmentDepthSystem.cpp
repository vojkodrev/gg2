#include "EquipmentDepthSystem.h"
#include <cstdint>

void equipmentDepthSystem(Context &ctx)
{
    ctx.data.player.equipment.weapon.base.depthY[0] = ctx.data.player.base.depthY[0];
    ctx.data.player.equipment.ammo.base.depthY[0] = ctx.data.player.base.depthY[0];

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        ctx.data.npc.equipment.weapon.base.depthY[i] = ctx.data.npc.base.depthY[i];
        ctx.data.npc.equipment.ammo.base.depthY[i] = ctx.data.npc.base.depthY[i];
    }
}
