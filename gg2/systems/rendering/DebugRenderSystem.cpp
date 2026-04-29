#include "DebugRenderSystem.h"
#include <SDL3/SDL.h>
#include "../../utils/collision/EntityAABB.h"
#include "../../structs/gameplay/ai/AStarPool.h"
#include "../../structs/gameplay/ai/AStarStatus.h"

static void renderColBox(SDL_Renderer *renderer, SDL_FRect col)
{
    SDL_FPoint center = entityColCenter(col);
    SDL_RenderRect(renderer, &col);
    SDL_FRect pt = {center.x - 1, center.y - 1, 2, 2};
    SDL_RenderFillRect(renderer, &pt);
}

void debugRenderSystem(const Context &ctx)
{
    SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 255);

    renderColBox(ctx.renderer, entityColAABB(ctx.data.player));

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        renderColBox(ctx.renderer, entityColAABB(ctx.data.npc, i));
        auto &patrol = ctx.data.npc.ai.patrol;
        float spawnX = ctx.data.npc.ai.spawn.x[i];
        float spawnY = ctx.data.npc.ai.spawn.y[i];
        for (uint32_t p = 0; p < ctx.data.npc.ai.patrolCount[i]; p++)
        {
            SDL_FRect pt = {spawnX + patrol.x[i][p] - 1, spawnY + patrol.y[i][p] - 1, 2, 2};
            SDL_RenderFillRect(ctx.renderer, &pt);
        }

        auto &ai = ctx.data.npc.ai;
        uint32_t pathLen = ai.pathLength[i];
        for (uint32_t p = 0; p < pathLen; p++)
        {
            float px = (float)ai.path.x[i][p];
            float py = (float)ai.path.y[i][p];
            SDL_FRect pt = {px - 1, py - 1, 2, 2};
            SDL_RenderFillRect(ctx.renderer, &pt);
            if (p + 1 < pathLen)
                SDL_RenderLine(ctx.renderer, px, py, (float)ai.path.x[i][p + 1], (float)ai.path.y[i][p + 1]);
        }
    }

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        renderColBox(ctx.renderer, entityColAABB(ctx.data.object, i));

    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 255, 80);
    for (int i = 0; i < ctx.astarPool.count; i++)
    {
        const AStarContext &a = ctx.astarPool.ctx[i];
        SDL_FRect rect = { (float)a.searchX, (float)a.searchY, (float)a.searchW, (float)a.searchH };
        SDL_RenderRect(ctx.renderer, &rect);
    }

    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
}
