#include "ResolveProjectileEffectCollision.h"
#include "ColIdIndex.h"
#include "../../../structs/core/constants/ProjectileConstants.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../effects/SpawnTextEffect.h"
#include "../../projectile/DestroyProjectile.h"
#include <algorithm>
#include <cstdlib>
#include <string>

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

        if (effect.projectileType[effectIndex] == ProjectileType::AutoAttack)
        {
            const int hp = ctx.data.npc.statistics.hp[npcIndex];
            const int damageRandom =
                (rand() % (PROJECTILE_DAMAGE_RANDOM_RANGE + 1)) -
                PROJECTILE_DAMAGE_RANDOM_RANGE / 2;
            const int projectileDamage = PROJECTILE_DAMAGE - damageRandom;
            const int nextHp = std::max(0, hp - projectileDamage);
            const int damage = hp - nextHp;
            ctx.data.npc.statistics.prevHp[npcIndex] = hp;
            ctx.data.npc.statistics.hpDirty[npcIndex] = hp != nextHp;
            ctx.data.npc.statistics.hp[npcIndex] = nextHp;
            if (damage > 0)
                spawnTextEffect(ctx, npcIndex, std::to_string(damage));
        }

        destroyProjectile(ctx, effectIndex);
    }
}
