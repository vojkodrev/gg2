#include "EquipmentFacingSystem.h"
#include "UpdateEntityFlipByParentFacing.h"
#include <cstdint>

void equipmentFacingSystem(Context &ctx)
{
    auto &playerWeaponFacing = ctx.data.player.equipment.weapon.base.facing;
    playerWeaponFacing.dirty[0] = false;
    bool playerWeaponFlipX = playerWeaponFacing.flipX[0];
    updateEntityFlipByParentFacing(
        ctx.data.player.base.facing,
        playerWeaponFacing,
        0);
    playerWeaponFacing.dirty[0] = playerWeaponFacing.flipX[0] != playerWeaponFlipX;

    auto &playerAmmoFacing = ctx.data.player.equipment.ammo.base.facing;
    playerAmmoFacing.dirty[0] = false;
    bool playerAmmoFlipX = playerAmmoFacing.flipX[0];
    updateEntityFlipByParentFacing(
        ctx.data.player.base.facing,
        playerAmmoFacing,
        0);
    playerAmmoFacing.dirty[0] = playerAmmoFacing.flipX[0] != playerAmmoFlipX;

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        auto &npcWeaponFacing = ctx.data.npc.equipment.weapon.base.facing;
        npcWeaponFacing.dirty[i] = false;
        bool npcWeaponFlipX = npcWeaponFacing.flipX[i];
        updateEntityFlipByParentFacing(
            ctx.data.npc.base.facing,
            npcWeaponFacing,
            i);
        npcWeaponFacing.dirty[i] = npcWeaponFacing.flipX[i] != npcWeaponFlipX;

        auto &npcAmmoFacing = ctx.data.npc.equipment.ammo.base.facing;
        npcAmmoFacing.dirty[i] = false;
        bool npcAmmoFlipX = npcAmmoFacing.flipX[i];
        updateEntityFlipByParentFacing(
            ctx.data.npc.base.facing,
            npcAmmoFacing,
            i);
        npcAmmoFacing.dirty[i] = npcAmmoFacing.flipX[i] != npcAmmoFlipX;
    }
}
