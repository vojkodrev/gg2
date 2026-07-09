#include "ResolveProjectileEffectCollision.h"
#include "ColIdIndex.h"
#include "../../attacks/ApplyAttackDamage.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/SerpentStingConstants.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../ai/monster/RefreshNpcAttackedTimerOrPursuingTarget.h"
#include "../../projectile/DestroyProjectile.h"
#include <algorithm>

void resolveProjectileEffectCollision(
    Context &ctx,
    uint32_t effectIndex,
    uint32_t otherId,
    ColType otherType)
{
    auto &effect = ctx.data.effect;

    if (otherType == ColType::Object)
    {
        destroyProjectile(ctx, effectIndex);
        return;
    }

    if (otherType == ColType::NPC)
    {
        const uint32_t npcIndex = colIdIndex(otherId);
        if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
            return;

        if (effect.parent.type[effectIndex] == EntityType::Player)
            refreshNpcAttackedTimerOrPursuingTarget(
                npcIndex,
                ctx,
                EntityType::Player,
                0);

        if (effect.projectileType[effectIndex] == ProjectileType::AutoAttack)
        {
            applyAttackDamage(
                ctx,
                EntityType::NPC,
                npcIndex,
                PROJECTILE_DAMAGE,
                PROJECTILE_DAMAGE_RANDOM_RANGE);
        }
        else if (effect.projectileType[effectIndex] == ProjectileType::SerpentSting)
        {
            ctx.data.npc.serpentStingDebuffTimer[npcIndex] =
                SERPENT_STING_DEBUFF_TIME;
        }
        else if (effect.projectileType[effectIndex] == ProjectileType::ConcussiveShot)
        {
            ctx.data.npc.concussiveShotDebuffTimer[npcIndex] =
                CONCUSSIVE_SHOT_DEBUFF_TIME;
        }

        destroyProjectile(ctx, effectIndex);
    }
}
