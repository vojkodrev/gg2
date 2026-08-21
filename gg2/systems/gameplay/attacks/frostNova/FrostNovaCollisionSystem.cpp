#include "FrostNovaCollisionSystem.h"
#include "../damage/ApplyAttackDamage.h"
#include "../debuff/AddDebuff.h"
#include "../debuff/RemoveDebuff.h"
#include "../../../structs/core/constants/FrostNovaConstants.h"
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

void frostNovaCollisionSystem(Context &ctx)
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
            effect.type[effectIndex] != EffectType::FrostNova ||
            effect.parent.type[effectIndex] != EntityType::Player)
            continue;

        const SDL_FRect frostNovaCol =
            mainEntityColAABB(effect.base, effectIndex);
        if (frostNovaCol.w <= 0.0f || frostNovaCol.h <= 0.0f)
            continue;

        SpatialHashQueryCandidates candidates;
        const int candidateCount =
            spatialHashQuery(spatialHash, 0, frostNovaCol, candidates);
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
            if (!SDL_HasRectIntersectionFloat(&frostNovaCol, &npcCol))
                continue;

            auto &debuff = npc.frostNovaDebuff;
            for (uint32_t slot = 0; slot < debuff.pool.count[npcIndex]; slot++)
            {
                if (debuff.pool.active[npcIndex][slot])
                    removeDebuff(debuff, npcIndex, static_cast<int>(slot));
            }

            addDebuff(
                debuff,
                npcIndex,
                effect.parent.type[effectIndex],
                effect.parent.id[effectIndex],
                FROST_NOVA_DEBUFF_TIME);

            applyAttackDamage(
                ctx,
                EntityType::NPC,
                npcIndex,
                npc.statistics,
                npc.group,
                npc.base,
                FROST_NOVA_DAMAGE,
                0);
        }
    }
}
