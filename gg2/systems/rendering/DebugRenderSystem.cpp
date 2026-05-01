#include "DebugRenderSystem.h"
#include <SDL3/SDL.h>
#include "../../utils/collision/EntityColAABBPlayer.h"
#include "../../utils/collision/EntityColAABBNPC.h"
#include "../../utils/collision/EntityColAABBObject.h"
#include "../../utils/collision/EntityColCenter.h"
#include "../../structs/gameplay/ai/AStarPool.h"
#include "../../structs/gameplay/ai/AStarStatus.h"
#include "../gameplay/camera/GetCameraOffset.h"

static void renderColBox(SDL_Renderer *renderer, SDL_FRect col, SDL_FPoint off)
{
    col.x += off.x;
    col.y += off.y;
    SDL_FPoint center = entityColCenter(col);
    SDL_RenderRect(renderer, &col);
    SDL_FRect pt = {center.x - 1, center.y - 1, 2, 2};
    SDL_RenderFillRect(renderer, &pt);
}

void debugRenderSystem(const Context &ctx)
{
    SDL_FPoint off = getCameraOffset(ctx);

    SDL_SetRenderDrawColor(ctx.renderer, 255, 0, 0, 255);

    renderColBox(ctx.renderer, entityColAABB(ctx.data.player), off);

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        renderColBox(ctx.renderer, entityColAABB(ctx.data.npc, i), off);
        auto &patrol = ctx.data.npc.ai.patrol;
        float spawnX = ctx.data.npc.ai.spawn.x[i];
        float spawnY = ctx.data.npc.ai.spawn.y[i];
        for (uint32_t p = 0; p < ctx.data.npc.ai.patrolCount[i]; p++)
        {
            SDL_FRect pt = {spawnX + patrol.x[i][p] - 1 + off.x, spawnY + patrol.y[i][p] - 1 + off.y, 2, 2};
            SDL_RenderFillRect(ctx.renderer, &pt);
        }

        auto &ai = ctx.data.npc.ai;
        uint32_t pathLen = ai.pathLength[i];
        for (uint32_t p = 0; p < pathLen; p++)
        {
            float px = (float)ai.path.x[i][p] + off.x;
            float py = (float)ai.path.y[i][p] + off.y;
            SDL_FRect pt = {px - 1, py - 1, 2, 2};
            SDL_RenderFillRect(ctx.renderer, &pt);
            if (p + 1 < pathLen)
                SDL_RenderLine(ctx.renderer, px, py, (float)ai.path.x[i][p + 1] + off.x, (float)ai.path.y[i][p + 1] + off.y);
        }
    }

    for (uint32_t i = 0; i < ctx.data.object.objectCount; i++)
        renderColBox(ctx.renderer, entityColAABB(ctx.data.object, i), off);

    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 255, 80);
    for (int i = 0; i < ctx.astarPool.count; i++)
    {
        const AStarContext &a = ctx.astarPool.ctx[i];
        SDL_FRect rect = { (float)a.searchX + off.x, (float)a.searchY + off.y, (float)a.searchW, (float)a.searchH };
        SDL_RenderRect(ctx.renderer, &rect);
    }

    SDL_SetRenderDrawColor(ctx.renderer, 0, 0, 0, 255);
}
