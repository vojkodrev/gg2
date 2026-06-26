#include "NpcMouseSelectSystem.h"

void npcMouseSelectSystem(Context &ctx)
{
    if (!ctx.data.action.mouseLeftReleased)
        return;

    ctx.data.player.previousSelectedNpc = ctx.data.player.selectedNpc;
    ctx.data.player.selectedNpc = -1;

    for (int i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        const SDL_FRect rect = {
            ctx.data.npc.base.position.x[i],
            ctx.data.npc.base.position.y[i],
            ctx.data.npc.base.position.w[i],
            ctx.data.npc.base.position.h[i]
        };
        const SDL_FPoint point = {ctx.mouse.worldX, ctx.mouse.worldY};

        if (SDL_PointInRectFloat(&point, &rect))
        {
            ctx.data.player.selectedNpc = i;
            return;
        }
    }
}
