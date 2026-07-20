#include "DebugRenderRangedDeadZone.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "PlayerConstants.h"
#include "../../../structs/equipment/WeaponType.h"

static void renderRangedDeadZone(const Context &ctx, const SDL_FPoint &center)
{
    const float radius = PLAYER_RANGED_ATTACK_MIN_DISTANCE;
    SDL_FRect rect = {
        center.x - radius + ctx.data.camera.offset.x,
        center.y - radius + ctx.data.camera.offset.y,
        radius * 2.0f,
        radius * 2.0f
    };

    if (SDL_HasRectIntersectionFloat(&rect, &ctx.data.camera.screen))
        SDL_RenderRect(ctx.renderer, &rect);
}

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
