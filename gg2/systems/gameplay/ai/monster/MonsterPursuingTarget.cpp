#include "MonsterPursuingTarget.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "SetNpcAiStateAttack.h"
#include "CanMonsterAttackTarget.h"

void monsterPursuingTarget(uint32_t n, Context &ctx)
{
    if (ctx.data.npc.ai.attackedTimer[n] <= 0.0f)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }

    const auto &target = ctx.data.npc.ai.target;
    if (!canMonsterAttackTarget(target.type[n]))
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }
    const SDL_FRect targetCol = getEntityColAABB(ctx, target.type[n], target.id[n]);

    if (areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    followAStarPathTo(n, ctx, targetCol);
}
