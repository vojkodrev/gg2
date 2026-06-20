#include "ResolveProjectileEffectCollision.h"
#include "ColIdIndex.h"
#include "../../../structs/npc/NPCAiType.h"
#include "../../../utils/effects/EffectFree.h"

void resolveProjectileEffectCollision(
    Context &ctx,
    uint32_t effectIndex,
    uint32_t otherId,
    ColType otherType)
{
    auto &effect = ctx.data.effect;

    if (otherType == ColType::Object)
    {
        effectFree(effect, ctx.data.groups, effectIndex);
        return;
    }

    if (otherType == ColType::NPC)
    {
        const uint32_t npcIndex = colIdIndex(otherId);
        if (ctx.data.npc.ai.type[npcIndex] == NPCAiType::Pet)
            return;

        effectFree(effect, ctx.data.groups, effectIndex);
    }
}
