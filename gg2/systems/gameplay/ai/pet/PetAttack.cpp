#include "PetAttack.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateIdle.h"
#include "SetNpcAiStatePursuingTarget.h"
#include "../monster/CanMonsterAttackTarget.h"

void petAttack(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];

    if (!canMonsterAttackTarget(targetType))
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
    if (!areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStatePursuingTarget(n, ctx, targetType, targetId);
        return;
    }
}
