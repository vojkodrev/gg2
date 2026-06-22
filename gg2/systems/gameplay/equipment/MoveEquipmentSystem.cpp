#include "MoveEquipmentSystem.h"
#include "AlignAmmoToWeaponAnchor.h"
#include "../../../utils/rect/AlignEntityToParentAnchor.h"

void moveEquipmentSystem(Context &ctx)
{
    if (ctx.data.player.base.position.dirty[0] || ctx.data.player.base.facing.dirty[0])
    {
        alignEntityToParentAnchor(
            ctx.data.player.equipment.weapon.base,
            ctx.data.player.base.animation,
            ctx.data.player.base.position,
            0);
        alignAmmoToWeaponAnchor(
            ctx.data.player.equipment.ammo.base,
            ctx.data.player.equipment.weapon.ammoAnchor,
            ctx.data.player.equipment.weapon.base,
            ctx.data.player.base,
            0);
    }

    for (uint32_t i = 0; i < ctx.data.npc.pool.count; i++)
    {
        if (!ctx.data.npc.pool.active[i])
            continue;

        if (!ctx.data.npc.base.position.dirty[i] && !ctx.data.npc.base.facing.dirty[i])
            continue;

        alignEntityToParentAnchor(
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base.animation,
            ctx.data.npc.base.position,
            i);
        alignAmmoToWeaponAnchor(
            ctx.data.npc.equipment.ammo.base,
            ctx.data.npc.equipment.weapon.ammoAnchor,
            ctx.data.npc.equipment.weapon.base,
            ctx.data.npc.base,
            i);
    }
}
