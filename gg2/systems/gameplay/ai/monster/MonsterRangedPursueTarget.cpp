#include "MonsterRangedPursueTarget.h"
#include "FollowMonsterPursueTarget.h"
#include "IsNpcTargetVisible.h"
#include "NpcMonsterConstants.h"
#include "PrepareMonsterPursueTarget.h"

void monsterRangedPursueTarget(Context &ctx, uint32_t n)
{
    auto &npc = ctx.data.npc;
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterPursueTarget(ctx, n, targetType, targetId, targetCol))
        return;

    if (npc.ai.targetVisibleTimer[n] <= 0.0f)
    {
        npc.ai.targetVisibleTimer[n] = NPC_TARGET_VISIBLE_CHECK_TIME;
        npc.ai.targetVisible[n] = isNpcTargetVisible(
            ctx,
            n,
            targetType,
            static_cast<uint32_t>(targetId),
            targetCol);
    }

    if (npc.ai.targetVisible[n])
        return;

    followMonsterPursueTarget(ctx, n, targetType, targetId, targetCol);
}
