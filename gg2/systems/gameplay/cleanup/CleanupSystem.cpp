#include "CleanupSystem.h"
#include "../../../structs/animation/AnimationState.h"
#include <cstring>

void cleanupSystem(Context &ctx)
{
    std::memset(ctx.data.player.base.position.dirty, 0, sizeof(ctx.data.player.base.position.dirty));
    std::memset(ctx.data.player.base.position.inputMovement, 0, sizeof(ctx.data.player.base.position.inputMovement));
    std::memset(ctx.data.player.base.facing.dirty, 0, sizeof(ctx.data.player.base.facing.dirty));
    std::memset(ctx.data.player.equipment.weapon.base.position.dirty, 0, sizeof(ctx.data.player.equipment.weapon.base.position.dirty));
    std::memset(ctx.data.player.equipment.weapon.base.facing.dirty, 0, sizeof(ctx.data.player.equipment.weapon.base.facing.dirty));
    std::memset(ctx.data.player.equipment.ammo.base.position.dirty, 0, sizeof(ctx.data.player.equipment.ammo.base.position.dirty));
    std::memset(ctx.data.player.equipment.ammo.base.facing.dirty, 0, sizeof(ctx.data.player.equipment.ammo.base.facing.dirty));
    std::memset(ctx.data.player.healthbar.base.position.dirty, 0, sizeof(ctx.data.player.healthbar.base.position.dirty));
    std::memset(ctx.data.player.healthbar.base.facing.dirty, 0, sizeof(ctx.data.player.healthbar.base.facing.dirty));
    std::memset(ctx.data.player.healthbar.dirty, 0, sizeof(ctx.data.player.healthbar.dirty));
    std::memset(ctx.data.player.manabar.dirty, 0, sizeof(ctx.data.player.manabar.dirty));
    std::memset(ctx.data.player.castbar.progressBar.dirty, 0, sizeof(ctx.data.player.castbar.progressBar.dirty));
    std::memset(ctx.data.player.statistics.health.dirty, 0, sizeof(ctx.data.player.statistics.health.dirty));
    std::memset(ctx.data.player.statistics.mana.dirty, 0, sizeof(ctx.data.player.statistics.mana.dirty));

    std::memset(ctx.data.npc.base.position.dirty, 0, sizeof(ctx.data.npc.base.position.dirty));
    std::memset(ctx.data.npc.base.facing.dirty, 0, sizeof(ctx.data.npc.base.facing.dirty));
    std::memset(ctx.data.npc.equipment.weapon.base.position.dirty, 0, sizeof(ctx.data.npc.equipment.weapon.base.position.dirty));
    std::memset(ctx.data.npc.equipment.weapon.base.facing.dirty, 0, sizeof(ctx.data.npc.equipment.weapon.base.facing.dirty));
    std::memset(ctx.data.npc.equipment.ammo.base.position.dirty, 0, sizeof(ctx.data.npc.equipment.ammo.base.position.dirty));
    std::memset(ctx.data.npc.equipment.ammo.base.facing.dirty, 0, sizeof(ctx.data.npc.equipment.ammo.base.facing.dirty));
    std::memset(ctx.data.npc.healthbar.base.position.dirty, 0, sizeof(ctx.data.npc.healthbar.base.position.dirty));
    std::memset(ctx.data.npc.healthbar.base.facing.dirty, 0, sizeof(ctx.data.npc.healthbar.base.facing.dirty));
    std::memset(ctx.data.npc.healthbar.dirty, 0, sizeof(ctx.data.npc.healthbar.dirty));
    std::memset(ctx.data.npc.manabar.dirty, 0, sizeof(ctx.data.npc.manabar.dirty));
    std::memset(ctx.data.npc.statistics.health.dirty, 0, sizeof(ctx.data.npc.statistics.health.dirty));
    std::memset(ctx.data.npc.statistics.mana.dirty, 0, sizeof(ctx.data.npc.statistics.mana.dirty));

    std::memset(ctx.data.object.base.position.dirty, 0, sizeof(ctx.data.object.base.position.dirty));
    std::memset(ctx.data.object.base.facing.dirty, 0, sizeof(ctx.data.object.base.facing.dirty));

    std::memset(ctx.data.effect.base.position.dirty, 0, sizeof(ctx.data.effect.base.position.dirty));
    std::memset(ctx.data.effect.base.facing.dirty, 0, sizeof(ctx.data.effect.base.facing.dirty));

    if (ctx.data.player.equipment.weapon.base.animation.animationState[0] == AnimationState::Finished)
        ctx.data.player.equipment.weapon.base.animation.animationState[0] = AnimationState::Idle;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (ctx.data.npc.equipment.weapon.base.animation.animationState[i] == AnimationState::Finished)
            ctx.data.npc.equipment.weapon.base.animation.animationState[i] = AnimationState::Idle;
    }
}
