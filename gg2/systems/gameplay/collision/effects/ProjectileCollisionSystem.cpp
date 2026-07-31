#include "ProjectileCollisionSystem.h"
#include "EntityColAABB.h"
#include "GetEntityColAABB.h"
#include "ResolveAutoAttackProjectile.h"
#include "ResolveConcussiveShotProjectile.h"
#include "ResolveSerpentStingProjectile.h"
#include "../../ai/monster/RefreshNpcAttackedTimer.h"
#include "../../projectile/DestroyProjectile.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../structs/npc/NPCAiType.h"
#include <SDL3/SDL.h>

void projectileCollisionSystem(Context &ctx)
{
    auto &effect = ctx.data.effect;

    for (uint32_t effectIndex = 0; effectIndex < effect.pool.count[0]; effectIndex++)
    {
        if (!effect.pool.active[0][effectIndex] ||
            effect.type[effectIndex] != EffectType::Projectile)
            continue;

        const EntityType targetType = effect.target.type[effectIndex];
        const int targetId = effect.target.id[effectIndex];
        const bool playerTargetIsValid =
            targetType == EntityType::Player && targetId == 0;
        const bool npcTargetIsValid =
            targetType == EntityType::NPC &&
            targetId >= 0 &&
            targetId < MAX_NPCS &&
            ctx.data.npc.active[targetId];
        if (!playerTargetIsValid && !npcTargetIsValid)
            continue;
        const uint32_t targetIndex = static_cast<uint32_t>(targetId);

        const SDL_FRect projectileCol = entityColAABB(effect.base, effectIndex);
        const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
        if (!SDL_HasRectIntersectionFloat(&projectileCol, &targetCol))
            continue;

        const EntityType parentType = effect.parent.type[effectIndex];
        const int parentId = effect.parent.id[effectIndex];
        if (targetType == EntityType::NPC)
        {
            const NPCAiType targetAiType = ctx.data.npc.ai.type[targetIndex];
            if (targetAiType == NPCAiType::MonsterMelee ||
                targetAiType == NPCAiType::MonsterRanged)
                refreshNpcAttackedTimer(ctx, targetIndex);
        }

        if (effect.projectileType[effectIndex] == ProjectileType::AutoAttack)
            resolveAutoAttackProjectile(
                ctx,
                targetType,
                targetIndex,
                parentType,
                parentId);
        else if (effect.projectileType[effectIndex] == ProjectileType::SerpentSting)
            resolveSerpentStingProjectile(ctx, targetIndex, parentType, parentId);
        else if (effect.projectileType[effectIndex] == ProjectileType::ConcussiveShot)
            resolveConcussiveShotProjectile(
                ctx,
                targetType,
                targetIndex,
                parentType,
                parentId);

        destroyProjectile(ctx, effectIndex);
    }
}
