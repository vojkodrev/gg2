#include "AoeEffectCollisionSystem.h"
#include "ResolveArcaneExplosion.h"
#include "ResolveFrostNova.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../utils/collision/ColIdIndex.h"
#include "../../../utils/collision/ColIdType.h"
#include "../../../utils/collision/ColType.h"
#include "../../../utils/collision/MainEntityColAABB.h"
#include "../../../utils/collision/spatialhash/SpatialHashQuery.h"
#include "../../../utils/collision/spatialhash/SpatialHashQueryCandidates.h"
#include <SDL3/SDL.h>
#include <shared_mutex>

void aoeEffectCollisionSystem(Context &ctx)
{
    auto &effect = ctx.data.effect;
    auto &npc = ctx.data.npc;
    const auto &spatialHash = ctx.collision.spatialHash;
    std::shared_lock lock(ctx.collision.spatialHashMutex);

    for (uint32_t effectIndex = 0;
        effectIndex < effect.pool.count[0];
        effectIndex++)
    {
        if (!effect.pool.active[0][effectIndex] ||
            (effect.type[effectIndex] != EffectType::FrostNova &&
                effect.type[effectIndex] != EffectType::ArcaneExplosion) ||
            effect.parent.type[effectIndex] != EntityType::Player)
            continue;

        const SDL_FRect effectCol =
            mainEntityColAABB(effect.base, effectIndex);
        if (effectCol.w <= 0.0f || effectCol.h <= 0.0f)
            continue;

        SpatialHashQueryCandidates candidates;
        const int candidateCount =
            spatialHashQuery(spatialHash, 0, effectCol, candidates);
        for (int candidateIndex = 0;
            candidateIndex < candidateCount;
            candidateIndex++)
        {
            const uint32_t candidate = candidates[candidateIndex];
            if (colIdType(candidate) != ColType::NPC)
                continue;

            const uint32_t npcIndex = colIdIndex(candidate);
            if (npcIndex >= MAX_NPCS ||
                !npc.active[npcIndex])
                continue;

            const SDL_FRect npcCol = mainEntityColAABB(npc.base, npcIndex);
            if (!SDL_HasRectIntersectionFloat(&effectCol, &npcCol))
                continue;

            if (effect.type[effectIndex] == EffectType::FrostNova)
                resolveFrostNova(
                    ctx,
                    npcIndex,
                    effect.parent.type[effectIndex],
                    effect.parent.id[effectIndex]);
            else if (effect.type[effectIndex] == EffectType::ArcaneExplosion)
                resolveArcaneExplosion(
                    ctx,
                    npcIndex,
                    effect.parent.type[effectIndex],
                    effect.parent.id[effectIndex]);
        }
    }
}
