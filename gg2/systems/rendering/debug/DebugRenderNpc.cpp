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
        for (uint32_t p = 0; p < patrol.count[i]; p++)
        {
            SDL_FRect pt = {spawnX + patrol.point.x[i][p] - 1 + off.x, spawnY + patrol.point.y[i][p] - 1 + off.y, 2, 2};
            if (SDL_HasRectIntersectionFloat(&pt, &screen))
                SDL_RenderFillRect(renderer, &pt);
        }

        auto &path = ctx.data.npc.ai.path;
        uint32_t pathLen = path.length[i];
        for (uint32_t p = 0; p < pathLen; p++)
        {
            float px = (float)path.point.x[i][p] + off.x;
            float py = (float)path.point.y[i][p] + off.y;
            SDL_FRect pt = {px - 1, py - 1, 2, 2};
            if (SDL_HasRectIntersectionFloat(&pt, &screen))
                SDL_RenderFillRect(renderer, &pt);
            if (p + 1 < pathLen)
                SDL_RenderLine(renderer, px, py, (float)path.point.x[i][p + 1] + off.x, (float)path.point.y[i][p + 1] + off.y);
        }
    }
}
