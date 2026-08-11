#include "DebugRenderNpc.h"
#include "DebugRenderEntityBase.h"
#include "DebugRenderEquipment.h"
#include "RenderDebugLine.h"
#include "RenderColBox.h"
#include "RenderColCenter.h"

void debugRenderNpc(const Context &ctx)
{
    SDL_Renderer *renderer = ctx.renderer;
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
    const bool showCollision = ctx.data.debug.showCollision;
    const bool showNavigation = ctx.data.debug.showNavigation;

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        if (!ctx.data.npc.active[i])
            continue;

        if (showCollision)
            debugRenderEntityBase(
                ctx,
                ctx.data.npc.base,
                i,
                SDL_Color{255, 0, 0, 255},
                SDL_Color{0, 255, 0, 255});

        debugRenderEquipment(ctx, ctx.data.npc.equipment, i);

        const int weaponFrameIndex =
            ctx.data.npc.equipment.weapon.base.animation.frameIndex[i];
        const auto &rangedCollision = ctx.data.npc.rangedCollision;
        const auto &rangedCollisionAnchor = rangedCollision.anchor;
        if (
            ctx.data.debug.showRangedWeaponCollision &&
            rangedCollisionAnchor.exists[i][weaponFrameIndex])
        {
            const SDL_FRect collision = {
                ctx.data.npc.base.position.x[i] +
                    rangedCollisionAnchor.offX[i][weaponFrameIndex],
                ctx.data.npc.base.position.y[i] +
                    rangedCollisionAnchor.offY[i][weaponFrameIndex],
                rangedCollisionAnchor.w[i][weaponFrameIndex],
                rangedCollisionAnchor.h[i][weaponFrameIndex]
            };
            SDL_SetRenderDrawColor(renderer, 0, 255, 128, 255);
            renderColBox(ctx, collision, false);

            const SDL_FPoint center = {
                collision.x + rangedCollision.center.x[i][weaponFrameIndex],
                collision.y + rangedCollision.center.y[i][weaponFrameIndex]
            };
            SDL_SetRenderDrawColor(renderer, 255, 64, 64, 255);
            renderColCenter(ctx, center, 4.0f);
        }

        if (showNavigation)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
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
                    renderDebugLine(
                        ctx,
                        px,
                        py,
                        (float)path.point.x[i][p + 1] + off.x,
                        (float)path.point.y[i][p + 1] + off.y);
            }
        }
    }
}
