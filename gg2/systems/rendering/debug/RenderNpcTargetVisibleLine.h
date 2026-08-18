#pragma once
#include "Context.h"
#include "MainEntityColAABB.h"
#include "RenderTargetVisibleLine.h"

inline void renderNpcTargetVisibleLine(
    const Context &ctx,
    uint32_t entityIndex)
{
    const auto &npc = ctx.data.npc;
    const auto &target = npc.ai.target;
    const EntityType targetType = target.type[entityIndex];
    const int targetId = target.id[entityIndex];
    SDL_FRect targetCol;
    if (targetType == EntityType::Player)
    {
        if (targetId != 0)
            return;
        targetCol = mainEntityColAABB(ctx.data.player.base, 0);
    }
    else if (targetType == EntityType::NPC)
    {
        if (targetId < 0 || targetId >= MAX_NPCS || !npc.active[targetId])
            return;
        targetCol = mainEntityColAABB(
            npc.base,
            static_cast<uint32_t>(targetId));
    }
    else
        return;

    renderTargetVisibleLine(ctx, npc.equipment, entityIndex, targetCol);
}
