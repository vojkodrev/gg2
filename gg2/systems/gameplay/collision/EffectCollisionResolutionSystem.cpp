#include "EffectCollisionResolutionSystem.h"
#include "ColIdIndex.h"
#include "ColIdType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../../utils/effects/EffectFree.h"

void effectCollisionResolutionSystem(Context &ctx)
{
    auto &cr = ctx.collision.effectCollisions;
    auto &effect = ctx.data.effect;

    for (uint32_t k = 0; k < cr.count; k++)
    {
        const uint32_t idA = cr.pair.a[k];
        const uint32_t idB = cr.pair.b[k];
        const ColType typeA = colIdType(idA);
        const ColType typeB = colIdType(idB);

        uint32_t effectId = 0;
        uint32_t otherId = 0;
        ColType otherType;

        if (typeA == ColType::Effect)
        {
            effectId = idA;
            otherId = idB;
            otherType = typeB;
        }
        else if (typeB == ColType::Effect)
        {
            effectId = idB;
            otherId = idA;
            otherType = typeA;
        }
        else
            continue;

        const uint32_t effectIndex = colIdIndex(effectId);
        if (!effect.pool.active[effectIndex])
            continue;

        if (effect.type[effectIndex] != EffectType::Projectile)
            continue;

        if (otherType == ColType::Object)
        {
            effectFree(effect, ctx.data.groups, effectIndex);
            continue;
        }

        if (otherType == ColType::NPC)
        {
            const uint32_t npcIndex = colIdIndex(otherId);
            if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
                continue;

            effectFree(effect, ctx.data.groups, effectIndex);
        }
    }
}
