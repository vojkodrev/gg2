#include "MonsterMeleePursueTarget.h"
#include "AreColBoxesNear.h"
#include "FollowMonsterPursueTarget.h"
#include "NpcMonsterConstants.h"
#include "PrepareMonsterPursueTarget.h"
#include "SetNpcAiStateAttack.h"

void monsterMeleePursueTarget(Context &ctx, uint32_t n)
{
    EntityType targetType;
    int targetId;
    SDL_FRect targetCol;
    if (!prepareMonsterPursueTarget(ctx, n, targetType, targetId, targetCol))
        return;

    if (areColBoxesNear(ctx, n, targetCol, NPC_MELEE_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    followMonsterPursueTarget(ctx, n, targetType, targetId, targetCol);
}
