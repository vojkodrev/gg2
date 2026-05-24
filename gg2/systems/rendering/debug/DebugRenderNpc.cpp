#include "DebugRenderNpc.h"
#include "RenderColBox.h"
#include "../../../utils/collision/EntityColAABBNPC.h"
#include "../../../utils/rect/EntityAnchorAABBNPC.h"
#include "../../../utils/collision/EntityWeaponColAABBNPC.h"
#include "../../../utils/rect/EntityWeaponAnchorAABBNPC.h"

void debugRenderNpc(const Context &ctx, SDL_FPoint off, const SDL_FRect &screen)
{
    SDL_Renderer *renderer = ctx.renderer;
    const bool showCollision = ctx.data.debug.showCollision;
    const bool showNavigation = ctx.data.debug.showNavigation;
    const bool showWeaponCollision = ctx.data.debug.showWeaponCollision;

    for (uint32_t i = 0; i < ctx.data.npc.npcCount; i++)
    {
        if (showCollision)
        {
            SDL_FRect col = entityColAABB(ctx.data.npc, i);
            if (col.w > 0.0f && col.h > 0.0f)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                renderColBox(renderer, col, off, screen);
            }

            SDL_FRect anchor = entityAnchorAABB(ctx.data.npc, i);
            if (anchor.w > 0.0f && anchor.h > 0.0f)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                renderColBox(renderer, anchor, off, screen);
            }
        }

        if (showWeaponCollision)
        {
            SDL_FRect weaponCol = entityWeaponColAABB(ctx.data.npc, i);
            if (weaponCol.w > 0.0f && weaponCol.h > 0.0f)
            {
                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                renderColBox(renderer, weaponCol, off, screen);
            }

            SDL_FRect weaponAnchor = entityWeaponAnchorAABB(ctx.data.npc, i);
            if (weaponAnchor.w > 0.0f && weaponAnchor.h > 0.0f)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                renderColBox(renderer, weaponAnchor, off, screen);
            }
        }

        if (showNavigation)
        {
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
}
