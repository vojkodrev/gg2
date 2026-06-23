#pragma once
#include "CollisionConstants.h"
#include "Context.h"
#include "GetEntityColAABB.h"
#include "spatialhash/SpatialHash.h"
#include "spatialhash/SpatialHashQuery.h"
#include <SDL3/SDL.h>
#include <cstdint>

inline void collectCollisionPairsForEntity(
    CollisionResult &cr,
    Context &ctx,
    uint32_t entityColId,
    SDL_FRect colBox,
    bool skipLowerIds)
{
    const auto &hash = ctx.collision.spatialHash;
    auto *candidates = ctx.collision.candidates;
    int n = spatialHashQuery(hash, colBox, candidates, SpatialHash::MAX_PER_BUCKET * 4);
    for (int k = 0; k < n; k++)
    {
        uint32_t other = candidates[k];
        if (other == entityColId)
            continue;

        if (skipLowerIds && other <= entityColId)
            continue;
        SDL_FRect ob = getEntityColAABB(ctx, other);
        if (SDL_HasRectIntersectionFloat(&colBox, &ob) && cr.count < MAX_COLLISION_PAIRS)
        {
            cr.pair.a[cr.count] = entityColId;
            cr.pair.b[cr.count] = other;
            cr.count++;
        }
    }
}
