#include "ProjectileCollisionSystem.h"
#include "EntityColAABB.h"
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

        if (effect.target.type[effectIndex] != EntityType::NPC)
            continue;

        const int targetId = effect.target.id[effectIndex];
        if (targetId < 0 || targetId >= MAX_NPCS || !ctx.data.npc.active[targetId])
            continue;
        const uint32_t npcIndex = (uint32_t)targetId;

        const SDL_FRect projectileCol = entityColAABB(effect.base, effectIndex);
        const SDL_FRect targetCol = entityColAABB(ctx.data.npc.base, targetId);
        if (!SDL_HasRectIntersectionFloat(&projectileCol, &targetCol))
            continue;

        if (ctx.data.npc.ai.type[targetId] == NPCAiType::Pet)
            continue;

        const EntityType parentType = effect.parent.type[effectIndex];
        const int parentId = effect.parent.id[effectIndex];
        if (parentType == EntityType::Player)
            refreshNpcAttackedTimer(ctx, npcIndex);

        if (effect.projectileType[effectIndex] == ProjectileType::AutoAttack)
            resolveAutoAttackProjectile(ctx, npcIndex, parentType, parentId);
        else if (effect.projectileType[effectIndex] == ProjectileType::SerpentSting)
            resolveSerpentStingProjectile(ctx, npcIndex, parentType, parentId);
        else if (effect.projectileType[effectIndex] == ProjectileType::ConcussiveShot)
            resolveConcussiveShotProjectile(ctx, npcIndex, parentType, parentId);

        destroyProjectile(ctx, effectIndex);
    }
}
