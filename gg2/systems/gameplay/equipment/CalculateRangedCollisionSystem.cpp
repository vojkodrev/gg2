#include "CalculateRangedCollisionSystem.h"
#include "../rotation/IsRotationAnimationFinished.h"
#include "../rotation/IsRotationAnimationRunning.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../utils/collision/MainEntityColAABB.h"
#include "../../../utils/collision/EntityColCenter.h"
#include <algorithm>
#include <cstdint>

void calculateRangedCollisionSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    for (uint32_t entityIndex = 0; entityIndex < MAX_NPCS; entityIndex++)
    {
        const auto &weapon = npc.equipment.weapon;
        if (!npc.active[entityIndex] ||
            !weapon.exists[entityIndex] ||
            weapon.type[entityIndex] != WeaponType::Ranged)
            continue;
        if (!weapon.base.facing.dirty[entityIndex] &&
            !isRotationAnimationRunning(weapon.base, entityIndex) &&
            !isRotationAnimationFinished(weapon.base, entityIndex))
            continue;

        const int frameIndex =
            weapon.base.animation.frameIndex[entityIndex];
        auto &rangedCollision = npc.rangedCollision;
        auto &anchor = rangedCollision.anchor;
        if (!anchor.exists[entityIndex][frameIndex][0])
            continue;

        const SDL_FRect npcCollisionWorld =
            mainEntityColAABB(npc.base, entityIndex);
        const SDL_FPoint npcCollisionCenterWorld =
            entityColCenter(npcCollisionWorld);
        const auto &ammoAnchor = weapon.ranged.ammoAnchor;
        SDL_FRect rangedCollisionWorld = npcCollisionWorld;
        if (ammoAnchor.exists[entityIndex][frameIndex][0])
        {
            const float ammoAnchorTop =
                weapon.base.position.y[entityIndex] +
                ammoAnchor.offY[entityIndex][frameIndex][0];
            float ammoTop = ammoAnchorTop;
            if (npc.equipment.ammo.exists[entityIndex])
            {
                const SDL_FRect ammoColBoxWorld =
                    mainEntityColAABB(
                        npc.equipment.ammo.base,
                        entityIndex);
                ammoTop = std::min(ammoColBoxWorld.y, ammoAnchorTop);
            }
            const SDL_FRect ammoCollisionWorld = {
                weapon.base.position.x[entityIndex] +
                    ammoAnchor.offX[entityIndex][frameIndex][0],
                ammoTop,
                ammoAnchor.w[entityIndex][frameIndex][0],
                ammoAnchorTop +
                    ammoAnchor.h[entityIndex][frameIndex][0] - ammoTop
            };
            SDL_GetRectUnionFloat(
                &npcCollisionWorld,
                &ammoCollisionWorld,
                &rangedCollisionWorld);
        }

        const float leftExtent =
            npcCollisionCenterWorld.x - rangedCollisionWorld.x;
        const float rightExtent =
            rangedCollisionWorld.x + rangedCollisionWorld.w -
            npcCollisionCenterWorld.x;
        const float horizontalExtent = std::max(leftExtent, rightExtent);
        rangedCollisionWorld.x =
            npcCollisionCenterWorld.x - horizontalExtent;
        rangedCollisionWorld.w = horizontalExtent * 2.0f;

        anchor.offX[entityIndex][frameIndex][0] =
            rangedCollisionWorld.x - npc.base.position.x[entityIndex];
        anchor.offY[entityIndex][frameIndex][0] =
            rangedCollisionWorld.y - npc.base.position.y[entityIndex];
        anchor.w[entityIndex][frameIndex][0] = rangedCollisionWorld.w;
        anchor.h[entityIndex][frameIndex][0] = rangedCollisionWorld.h;
        rangedCollision.center.x[entityIndex][frameIndex] =
            npcCollisionCenterWorld.x - rangedCollisionWorld.x;
        rangedCollision.center.y[entityIndex][frameIndex] =
            npcCollisionCenterWorld.y - rangedCollisionWorld.y;
    }
}
