#include "MonsterRangedPursueTarget.h"
#include "FollowMonsterPursueTarget.h"
#include "IsMonsterRangedTargetVisible.h"
#include "PrepareMonsterPursueTarget.h"
#include "../SetNpcAiStateAttack.h"

void monsterRangedPursueTarget(Context &ctx, uint32_t n)
{
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterPursueTarget(ctx, n, targetType, targetId, targetCol))
        return;

    if (isMonsterRangedTargetVisible(
            ctx,
            n,
            targetType,
            targetId,
            targetCol))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    followMonsterPursueTarget(ctx, n, targetType, targetId, targetCol);
}
