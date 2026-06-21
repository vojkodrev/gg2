#include "CleanupSystem.h"
#include "CleanupEntityBase.h"
#include "CleanupStatistics.h"

void cleanupSystem(Context &ctx)
{
    cleanupEntityBase(ctx.data.player.base, 1);
    cleanupEntityBase(ctx.data.player.equipment.weapon.base, 1);
    cleanupEntityBase(ctx.data.player.equipment.ammo.base, 1);
    cleanupEntityBase(ctx.data.player.healthbar.base, 1);
    cleanupStatistics(ctx.data.player.statistics, 1);

    cleanupEntityBase(ctx.data.npc.base, ctx.data.npc.npcCount);
    cleanupEntityBase(ctx.data.npc.equipment.weapon.base, ctx.data.npc.npcCount);
    cleanupEntityBase(ctx.data.npc.equipment.ammo.base, ctx.data.npc.npcCount);
    cleanupEntityBase(ctx.data.npc.healthbar.base, ctx.data.npc.npcCount);
    cleanupStatistics(ctx.data.npc.statistics, ctx.data.npc.npcCount);

    cleanupEntityBase(ctx.data.object.base, ctx.data.object.objectCount);
    cleanupEntityBase(ctx.data.effect.base, ctx.data.effect.pool.count);
}
