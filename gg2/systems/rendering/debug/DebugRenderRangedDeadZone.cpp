#include "DebugRenderRangedDeadZone.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "RenderRangedDeadZone.h"
#include "../../../structs/equipment/WeaponType.h"

void debugRenderRangedDeadZone(const Context &ctx)
{
    if (!ctx.data.debug.showRangedDeadZone)
        return;

    SDL_SetRenderDrawColor(ctx.renderer, 255, 128, 0, 255);

    const auto &player = ctx.data.player;
    if (player.equipment.weapon.type[0] == WeaponType::Ranged)
        renderRangedDeadZone(
            ctx,
            entityColCenter(entityColAABB(player.base, 0)));

    const auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!npc.active[i] || npc.equipment.weapon.type[i] != WeaponType::Ranged)
            continue;

        renderRangedDeadZone(
            ctx,
            entityColCenter(entityColAABB(npc.base, i)));
    }
}
