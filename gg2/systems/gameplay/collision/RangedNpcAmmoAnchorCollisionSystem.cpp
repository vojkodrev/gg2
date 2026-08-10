#include "RangedNpcAmmoAnchorCollisionSystem.h"
#include "../../../utils/collision/GetRangedAmmoAnchorNpcColAABB.h"
#include "../../../structs/collision/SpatialHashQueryCandidates.h"
#include "../../../structs/equipment/WeaponType.h"
#include "../../../utils/collision/ColIdIndex.h"
#include "../../../utils/collision/ColIdType.h"
#include "../../../utils/collision/EntityColAABB.h"
#include "../../../utils/collision/spatialhash/SpatialHashQuery.h"
#include <algorithm>
#include <shared_mutex>

void rangedNpcAmmoAnchorCollisionSystem(Context &ctx)
{
    auto &npc = ctx.data.npc;
    const auto &object = ctx.data.object;
    const auto &spatialHash = ctx.collision.spatialHash;
    std::shared_lock lock(ctx.collision.spatialHashMutex);

    for (uint32_t i = 0; i < MAX_NPCS; i++)
    {
        const auto &weapon = npc.equipment.weapon;
        const int frameIndex = weapon.base.animation.frameIndex[i];
        if (!npc.active[i] ||
            !weapon.exists[i] ||
            weapon.type[i] != WeaponType::Ranged ||
            !weapon.ranged.ammoAnchor.exists[i][frameIndex])
            continue;

        SDL_FRect moverBox =
            getRangedAmmoAnchorNpcColAABB(ctx, i);
        SpatialHashQueryCandidates candidates;
        const int candidateCount =
            spatialHashQuery(spatialHash, 0, moverBox, candidates);
        for (int j = 0; j < candidateCount; j++)
        {
            const uint32_t id = candidates[j];
            if (colIdType(id) != ColType::Object)
                continue;

            const SDL_FRect obstacle =
                entityColAABB(object.base, colIdIndex(id));
            const float overlapX =
                std::min(moverBox.x + moverBox.w, obstacle.x + obstacle.w) -
                std::max(moverBox.x, obstacle.x);
            const float overlapY =
                std::min(moverBox.y + moverBox.h, obstacle.y + obstacle.h) -
                std::max(moverBox.y, obstacle.y);
            if (overlapX <= 0.0f || overlapY <= 0.0f)
                continue;

            SDL_FPoint offset = {};
            if (overlapX < overlapY)
                offset.x = moverBox.x < obstacle.x ? -overlapX : overlapX;
            else
                offset.y = moverBox.y < obstacle.y ? -overlapY : overlapY;

            npc.base.position.x[i] += offset.x;
            npc.base.position.y[i] += offset.y;
            npc.base.position.dirty[i] = true;
            moverBox.x += offset.x;
            moverBox.y += offset.y;
        }
    }
}
