#include "CreateNpcSelectorSystem.h"
#include "../../../../structs/effect/DestroyEffectType.h"
#include "../../../../structs/effect/EffectType.h"
#include "../../../../structs/effect/ParentType.h"
#include "../../../../utils/entity/CopyEntityBaseSlot.h"
#include "../../effects/EffectAlloc.h"

void createNpcSelectorSystem(Context &ctx)
{
    auto &player = ctx.data.player;
    if (player.previousSelectedNpc == player.selectedNpc)
        return;

    const int npcIndex = player.selectedNpc;
    const int effectIndex =
        effectAlloc(ctx.data.effect, ctx.data.groups, ctx.data.npc.groupId[npcIndex]);
    if (effectIndex == -1)
        return;

    copyEntityBaseSlot(
        ctx.data.effectTemplate.base,
        ctx.data.effectTemplate.selectOffset,
        ctx.data.effect.base,
        effectIndex);

    ctx.data.effect.type[effectIndex] = EffectType::Selector;
    ctx.data.effect.destroyType[effectIndex] = DestroyEffectType::None;
    ctx.data.effect.destroyDistance[effectIndex] = 0.0f;
    ctx.data.effect.destroyTimer[effectIndex] = 0.0f;
    ctx.data.effect.parent.type[effectIndex] = ParentType::NPC;
    ctx.data.effect.parent.id[effectIndex] = npcIndex;
    ctx.data.effect.start.x[effectIndex] = 0.0f;
    ctx.data.effect.start.y[effectIndex] = 0.0f;
    ctx.data.effect.target.x[effectIndex] = 0.0f;
    ctx.data.effect.target.y[effectIndex] = 0.0f;
    ctx.data.effect.base.position.x[effectIndex] =
        ctx.data.npc.base.position.x[npcIndex] +
        (ctx.data.npc.base.position.w[npcIndex] - ctx.data.effect.base.position.w[effectIndex]) * 0.5f;
    ctx.data.effect.base.position.y[effectIndex] =
        ctx.data.npc.base.position.y[npcIndex] -
        (ctx.data.effect.base.position.h[effectIndex] - ctx.data.npc.base.position.h[npcIndex]) * 0.5f;
    ctx.data.effect.base.position.dirty[effectIndex] = true;
    ctx.data.effect.base.depthY[effectIndex] = ctx.data.npc.base.depthY[npcIndex];

    player.selectedEffectId = effectIndex;
}
