#include "ResolveProjectileEffectCollision.h"
#include "ColIdIndex.h"
#include "../../attacks/ApplyAttackDamage.h"
#include "../../attacks/debuff/AddDebuff.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../../structs/core/constants/ConcussiveShotConstants.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/core/constants/SerpentStingConstants.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../ai/monster/RefreshNpcAttackedTimer.h"
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
        const EntityType parentType = effect.parent.type[effectIndex];
        const int parentId = effect.parent.id[effectIndex];
        if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
            return;

        if (parentType == EntityType::Player)
            refreshNpcAttackedTimer(ctx, npcIndex);

        if (effect.projectileType[effectIndex] == ProjectileType::AutoAttack)
        {
            const int damage = applyAttackDamage(
                ctx,
                EntityType::NPC,
                npcIndex,
                ctx.data.npc.statistics,
                ctx.data.npc.group,
                ctx.data.npc.base,
                PROJECTILE_DAMAGE,
                PROJECTILE_DAMAGE_RANDOM_RANGE);

            addToAggroTableValue(
                ctx.data.npc.aggroTable,
                npcIndex,
                parentType,
                parentId,
                (float)damage);
        }
        else if (effect.projectileType[effectIndex] == ProjectileType::SerpentSting)
        {
            addDebuff(
                ctx.data.npc.serpentStingDebuff,
                npcIndex,
                parentType,
                parentId,
                SERPENT_STING_DEBUFF_TIME);

            addToAggroTableValue(
                ctx.data.npc.aggroTable,
                npcIndex,
                parentType,
                parentId,
                0.0f);
        }
        else if (effect.projectileType[effectIndex] == ProjectileType::ConcussiveShot)
        {
            addDebuff(
                ctx.data.npc.concussiveShotDebuff,
                npcIndex,
                parentType,
                parentId,
                CONCUSSIVE_SHOT_DEBUFF_TIME);

            addToAggroTableValue(
                ctx.data.npc.aggroTable,
                npcIndex,
                parentType,
                parentId,
                CONCUSSIVE_SHOT_AGGRO_VALUE);
        }

        destroyProjectile(ctx, effectIndex);
    }
}
