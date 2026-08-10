#include "CalculateRangedCollisionSystem.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include <algorithm>
#include <cstdint>

void calculateRangedCollisionSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        const auto &weapon = npc.equipment.weapon;
        if (!npc.active[i] || weapon.type[i] != WeaponType::Ranged)
            continue;

        const int frameIndex = weapon.base.animation.frameIndex[i];
        auto &rangedCollision = npc.rangedCollision;
        auto &anchor = rangedCollision.anchor;
        if (!anchor.exists[i][frameIndex])
            continue;

        const SDL_FRect npcCollisionWorld = entityColAABB(npc.base, i);
        const SDL_FPoint npcCollisionCenterWorld =
            entityColCenter(npcCollisionWorld);
        const auto &ammoAnchor = weapon.ranged.ammoAnchor;
        SDL_FRect rangedCollisionWorld = npcCollisionWorld;
        if (ammoAnchor.exists[i][frameIndex])
        {
            const float ammoAnchorTop =
                weapon.base.position.y[i] + ammoAnchor.offY[i][frameIndex];
            float ammoTop = ammoAnchorTop;
            if (npc.equipment.ammo.exists[i])
            {
                const SDL_FRect ammoColBoxWorld =
                    entityColAABB(npc.equipment.ammo.base, i);
                ammoTop = std::min(ammoColBoxWorld.y, ammoAnchorTop);
            }
            const SDL_FRect ammoCollisionWorld = {
                weapon.base.position.x[i] + ammoAnchor.offX[i][frameIndex],
                ammoTop,
                ammoAnchor.w[i][frameIndex],
                ammoAnchorTop + ammoAnchor.h[i][frameIndex] - ammoTop
            };
            SDL_GetRectUnionFloat(
                &npcCollisionWorld,
                &ammoCollisionWorld,
                &rangedCollisionWorld);
        }

        anchor.offX[i][frameIndex] =
            rangedCollisionWorld.x - npc.base.position.x[i];
        anchor.offY[i][frameIndex] =
            rangedCollisionWorld.y - npc.base.position.y[i];
        anchor.w[i][frameIndex] = rangedCollisionWorld.w;
        anchor.h[i][frameIndex] = rangedCollisionWorld.h;
        rangedCollision.center.x[i][frameIndex] =
            npcCollisionCenterWorld.x - rangedCollisionWorld.x;
        rangedCollision.center.y[i][frameIndex] =
            npcCollisionCenterWorld.y - rangedCollisionWorld.y;
    }
}
