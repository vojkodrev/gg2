#pragma once
#include "Context.h"
#include "EntityColAABB.h"
#include "EntityColCenter.h"
#include "EntityColCenterWorld.h"
#include "RenderDebugLine.h"

inline void renderNpcTargetVisibleLine(const Context &ctx, uint32_t i)
{
    const auto &npc = ctx.data.npc;
    const auto &target = npc.ai.target;
    const EntityType targetType = target.type[i];
    const int targetId = target.id[i];
    SDL_FRect targetCol;
    if (targetType == EntityType::Player)
    {
        if (targetId != 0)
            return;
        targetCol = entityColAABB(ctx.data.player.base, 0);
    }
    else if (targetType == EntityType::NPC)
    {
        if (targetId < 0 || targetId >= MAX_NPCS || !npc.active[targetId])
            return;
        targetCol = entityColAABB(npc.base, static_cast<uint32_t>(targetId));
    }
    else
        return;

    const auto &equipment = npc.equipment;
    const SDL_FRect ammoAnchor = {
        equipment.weapon.ammoAnchor.offX[i][0],
        equipment.weapon.ammoAnchor.offY[i][0],
        equipment.weapon.ammoAnchor.w[i][0],
        equipment.weapon.ammoAnchor.h[i][0]
    };
    const SDL_FPoint ammoAnchorCenter = entityColCenterWorld(
        ammoAnchor,
        equipment.weapon.base.position,
        i);
    const SDL_FPoint targetCenter = entityColCenter(targetCol);
    const SDL_FPoint offset = ctx.data.camera.offset;

    renderDebugLine(
        ctx,
        ammoAnchorCenter.x + offset.x,
        ammoAnchorCenter.y + offset.y,
        targetCenter.x + offset.x,
        targetCenter.y + offset.y);
}
