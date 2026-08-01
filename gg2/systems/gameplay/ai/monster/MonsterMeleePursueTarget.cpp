#include "MonsterMeleePursueTarget.h"
#include "FollowMonsterPursueTarget.h"
#include "PrepareMonsterPursueTarget.h"
#include "SetNpcAiStateAttack.h"

void monsterMeleePursueTarget(Context &ctx, uint32_t n)
{
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterPursueTarget(ctx, n, targetType, targetId, targetCol))
        return;

    const bool goalReached = followMonsterPursueTarget(
        ctx,
        n,
        targetType,
        targetId,
        targetCol);
    if (goalReached)
        setNpcAiStateAttack(n, ctx);
}
