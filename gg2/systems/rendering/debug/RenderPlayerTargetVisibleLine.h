#pragma once
#include "Context.h"
#include "EntityColAABB.h"
#include "RenderTargetVisibleLine.h"

inline void renderPlayerTargetVisibleLine(const Context &ctx)
{
    const auto &player = ctx.data.player;
    const int targetId = player.selectedNpc;
    if (targetId < 0 || targetId >= MAX_NPCS ||
        !ctx.data.npc.active[targetId])
        return;

    renderTargetVisibleLine(
        ctx,
        player.equipment,
        0,
        entityColAABB(
            ctx.data.npc.base,
            static_cast<uint32_t>(targetId)));
}
