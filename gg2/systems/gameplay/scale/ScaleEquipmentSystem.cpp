#include "ScaleEquipmentSystem.h"
#include "ScaleAnimationFrames.h"

void scaleEquipmentSystem(Context &ctx)
{
    scaleAnimationFrames(ctx.data.player.equipment.weapon.animation, ctx.data.player.equipment.weapon.scale, 1);
    scaleAnimationFrames(
        ctx.data.npc.equipment.weapon.animation,
        ctx.data.npc.equipment.weapon.scale,
        ctx.data.npc.npcCount);
}
