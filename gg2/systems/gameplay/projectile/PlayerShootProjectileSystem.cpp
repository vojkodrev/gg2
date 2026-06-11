#include "PlayerShootProjectileSystem.h"
#include "../../../utils/pool/PoolAlloc.h"
#include "../../../utils/entity/CopyEntityBaseSlot.h"

void playerShootProjectileSystem(Context &ctx)
{
    if (ctx.data.action.digit1Released)
    {
        const auto &playerAmmo = ctx.data.player.equipment.ammo.base;
        const auto &playerWeapon = ctx.data.player.equipment.weapon;
        if (!playerWeapon.hasAmmo[0])
            return;

        int effectIndex = poolAlloc(ctx.data.effect.pool);
        if (effectIndex == -1)
            return;

        ctx.data.effect.groupId[effectIndex] = ctx.data.player.groupId;
        copyEntityBaseSlot(playerAmmo, 0, ctx.data.effect.base, effectIndex);
        ctx.data.player.equipment.weapon.showAmmo[0] = false;
    }
}
