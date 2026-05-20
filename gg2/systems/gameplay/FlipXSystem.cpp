#include "FlipXSystem.h"

template<int N>
static inline void updateEntityFlip(Facing<N> &facing, uint32_t i)
{
    facing.flipX[i] = facing.facing[i] != facing.initialFacing[i];
}

template<int N>
static inline void updateWeaponFlip(const Facing<N> &parentFacing, Facing<N> &weaponFacing, uint32_t i)
{
    bool parentNeedsFlip = parentFacing.facing[i] != weaponFacing.initialFacing[i];
    bool weaponFacingChanged = weaponFacing.facing[i] != weaponFacing.initialFacing[i];
    weaponFacing.flipX[i] = parentNeedsFlip != weaponFacingChanged;
}

void flipXSystem(Context &ctx)
{
    updateEntityFlip(ctx.data.player.facing, 0);
    updateWeaponFlip(ctx.data.player.facing, ctx.data.player.equipment.weapon.facing, 0);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        updateEntityFlip(ctx.data.npc.facing, i);
        updateWeaponFlip(ctx.data.npc.facing, ctx.data.npc.equipment.weapon.facing, i);
    }
}
