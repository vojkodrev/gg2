#include "PetTaunt.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "../../../structs/core/constants/ZIndexConstants.h"
#include "../../../structs/core/constants/TauntConstants.h"
#include "../../../structs/effect/DestroyEffectType.h"
#include "../../../structs/effect/EffectType.h"
#include "../../effects/CopyEffect.h"
#include "../../attacks/aggroTable/AddToAggroTableValue.h"
#include "../../attacks/aggroTable/FindAggroTableSlotByEntityId.h"
#include "../../attacks/aggroTable/FindNextHighestAggroTableValue.h"
#include "../../effects/EffectAlloc.h"

void petTaunt(Context &ctx, uint32_t n)
{
    auto &mana = ctx.data.npc.statistics.mana;
    if (mana.mana[n] < TAUNT_MANA_COST)
        return;

    const int targetId = ctx.data.npc.ai.target.id[n];

    const int targetGroupId = ctx.data.npc.group.id[targetId];
    const int effectIndex = effectAlloc(ctx.data.effect, ctx.data.groups, targetGroupId);
    if (effectIndex == INVALID_ID)
        return;

    copyEffect(
        ctx,
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.tauntIndex,
        effectIndex);

    ctx.data.effect.type[effectIndex] = EffectType::Taunt;
    ctx.data.effect.zIndex[effectIndex] = EFFECT_TAUNT_Z_INDEX;
    ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::AnimationEnd;
    ctx.data.effect.parent.type[effectIndex] = EntityType::NPC;
    ctx.data.effect.parent.id[effectIndex] = targetId;
    ctx.data.npc.tauntTimer[n] = TAUNT_COOLDOWN_TIME;
    mana.mana[n] -= TAUNT_MANA_COST;
    mana.dirty[n] = true;

    auto &aggroTable = ctx.data.npc.aggroTable;
    const int petSlot = findAggroTableSlotByEntityId(
        aggroTable,
        targetId,
        EntityType::NPC,
        (int)n);
    const float petAggro = petSlot == INVALID_ID
        ? 0.0f
        : aggroTable.value[targetId][petSlot];
    const bool petHasTopAggro =
        aggroTable.maxEntityType[targetId] == EntityType::NPC &&
        aggroTable.maxEntityId[targetId] == (int)n;

    float aggroToAdd = 0.0f;
    if (!petHasTopAggro)
    {
        aggroToAdd = aggroTable.maxValue[targetId] - petAggro + TAUNT_AGGRO_BONUS;
    }
    else
    {
        const float nextHighestAggro = findNextHighestAggroTableValue(
            aggroTable,
            targetId,
            petSlot);
        if (petAggro - nextHighestAggro > TAUNT_AGGRO_BONUS)
            aggroToAdd = TAUNT_AGGRO_BONUS;
    }

    if (aggroToAdd > 0.0f)
    {
        addToAggroTableValue(
            aggroTable,
            targetId,
            EntityType::NPC,
            (int)n,
            aggroToAdd);
    }
}
