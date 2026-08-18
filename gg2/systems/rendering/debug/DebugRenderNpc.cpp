#include "DebugRenderNpc.h"
#include "DebugRenderEntityBase.h"
#include "DebugRenderEquipment.h"
#include "RenderDebugLine.h"
#include "RenderColBox.h"
#include "RenderColCenter.h"

void debugRenderNpc(const Context &ctx)
{
    const auto &debug = ctx.data.debug;
    if (
        !debug.showCollision &&
        !debug.showNavigation &&
        !debug.showWeaponCollision &&
        !debug.showRangedWeaponCollision &&
        !debug.showAmmoCollision)
        return;

    SDL_Renderer *renderer = ctx.renderer;
    const SDL_FPoint off = ctx.data.camera.offset;
    const SDL_FRect screen = ctx.data.camera.screen;
    const bool showCollision = debug.showCollision;
    const bool showNavigation = debug.showNavigation;
    const bool showEquipmentCollision =
        debug.showWeaponCollision || debug.showAmmoCollision;
    const bool showRangedWeaponCollision =
        debug.showRangedWeaponCollision;

    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        if (!ctx.data.npc.active[entityIndex])
            continue;

        if (showCollision)
            debugRenderEntityBase(
                ctx,
                ctx.data.npc.base,
                entityIndex,
                SDL_Color{255, 0, 0, 255},
                SDL_Color{0, 255, 0, 255});

        if (showEquipmentCollision)
            debugRenderEquipment(
                ctx,
                ctx.data.npc.equipment,
                entityIndex);

        if (showRangedWeaponCollision)
        {
            const int weaponFrameIndex =
                ctx.data.npc.equipment.weapon.base.animation
                    .frameIndex[entityIndex];
            const auto &rangedCollision = ctx.data.npc.rangedCollision;
            const auto &rangedCollisionAnchor = rangedCollision.anchor;
            if (rangedCollisionAnchor
                    .exists[entityIndex][weaponFrameIndex][0])
            {
                const SDL_FRect collision = {
                    ctx.data.npc.base.position.x[entityIndex] +
                        rangedCollisionAnchor
                            .offX[entityIndex][weaponFrameIndex][0],
                    ctx.data.npc.base.position.y[entityIndex] +
                        rangedCollisionAnchor
                            .offY[entityIndex][weaponFrameIndex][0],
                    rangedCollisionAnchor
                        .w[entityIndex][weaponFrameIndex][0],
                    rangedCollisionAnchor
                        .h[entityIndex][weaponFrameIndex][0]
                };
                SDL_SetRenderDrawColor(renderer, 0, 255, 128, 255);
                renderColBox(ctx, collision, false);

                const SDL_FPoint center = {
                    collision.x +
                        rangedCollision.center.x[entityIndex][weaponFrameIndex],
                    collision.y +
                        rangedCollision.center.y[entityIndex][weaponFrameIndex]
                };
                SDL_SetRenderDrawColor(renderer, 255, 64, 64, 255);
                renderColCenter(ctx, center, 4.0f);
            }
        }

        if (showNavigation)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            auto &patrol = ctx.data.npc.ai.patrol;
            float spawnX = ctx.data.npc.ai.spawn.x[entityIndex];
            float spawnY = ctx.data.npc.ai.spawn.y[entityIndex];
            for (uint32_t p = 0; p < patrol.count[entityIndex]; p++)
            {
                SDL_FRect pt = {
                    spawnX + patrol.point.x[entityIndex][p] - 1 + off.x,
                    spawnY + patrol.point.y[entityIndex][p] - 1 + off.y,
                    2,
                    2
                };
                if (SDL_HasRectIntersectionFloat(&pt, &screen))
                    SDL_RenderFillRect(renderer, &pt);
            }

            auto &path = ctx.data.npc.ai.path;
            uint32_t pathLen = path.length[entityIndex];
            for (uint32_t p = 0; p < pathLen; p++)
            {
                float px = (float)path.point.x[entityIndex][p] + off.x;
                float py = (float)path.point.y[entityIndex][p] + off.y;
                SDL_FRect pt = {px - 1, py - 1, 2, 2};
                if (SDL_HasRectIntersectionFloat(&pt, &screen))
                    SDL_RenderFillRect(renderer, &pt);
                if (p + 1 < pathLen)
                    renderDebugLine(
                        ctx,
                        px,
                        py,
                        (float)path.point.x[entityIndex][p + 1] + off.x,
                        (float)path.point.y[entityIndex][p + 1] + off.y);
            }
        }
    }
}
