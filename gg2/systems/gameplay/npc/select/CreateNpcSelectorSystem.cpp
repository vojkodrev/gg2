#include "CreateNpcSelectorSystem.h"
#include "../../../../structs/core/constants/IndexConstants.h"
#include "../../../../structs/effect/EffectType.h"
#include "../../../../structs/entity/EntityType.h"
#include "../../effects/CopyEffect.h"
#include "../../effects/EffectAlloc.h"
#include "PlaceNpcSelector.h"

void createNpcSelectorSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    if (player.selectedNpc == INVALID_ID || player.selectedEffectId != INVALID_ID)
        return;

    if (player.previousSelectedNpc == player.selectedNpc)
        return;

    const int npcIndex = player.selectedNpc;
    const int effectIndex =
        effectAlloc(ctx.data.effect, ctx.data.groups, ctx.data.npc.group.id[npcIndex]);
    if (effectIndex == INVALID_ID)
        return;

    copyEffect(
        ctx,
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.selectIndex,
        effectIndex);

    ctx.data.effect.type[effectIndex] = EffectType::Selector;
    ctx.data.effect.parent.type[effectIndex] = EntityType::NPC;
    ctx.data.effect.parent.id[effectIndex] = npcIndex;
    placeNpcSelector(ctx, effectIndex, npcIndex);
    ctx.data.effect.base.depthY[effectIndex] = ctx.data.npc.base.depthY[npcIndex];

    player.selectedEffectId = effectIndex;
}
