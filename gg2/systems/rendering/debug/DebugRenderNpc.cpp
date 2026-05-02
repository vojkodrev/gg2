#include "DebugRenderNpc.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABBNPC.h"

void debugRenderNpc(SDL_Renderer *renderer, const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        renderColBox(renderer, entityColAABB(ctx.data.npc, i), off, screen);
        auto &patrol = ctx.data.npc.ai.patrol;
        float spawnX = ctx.data.npc.ai.spawn.x[i];
        float spawnY = ctx.data.npc.ai.spawn.y[i];
        for (uint32_t p = 0; p < ctx.data.npc.ai.patrolCount[i]; p++)
        {
            SDL_FRect pt = {spawnX + patrol.x[i][p] - 1 + off.x, spawnY + patrol.y[i][p] - 1 + off.y, 2, 2};
            if (SDL_HasRectIntersectionFloat(&pt, &screen))
                SDL_RenderFillRect(renderer, &pt);
        }

        auto &ai = ctx.data.npc.ai;
        uint32_t pathLen = ai.pathLength[i];
        for (uint32_t p = 0; p < pathLen; p++)
        {
            float px = (float)ai.path.x[i][p] + off.x;
            float py = (float)ai.path.y[i][p] + off.y;
            SDL_FRect pt = {px - 1, py - 1, 2, 2};
            if (SDL_HasRectIntersectionFloat(&pt, &screen))
                SDL_RenderFillRect(renderer, &pt);
            if (p + 1 < pathLen)
                SDL_RenderLine(renderer, px, py, (float)ai.path.x[i][p + 1] + off.x, (float)ai.path.y[i][p + 1] + off.y);
        }
    }
}
