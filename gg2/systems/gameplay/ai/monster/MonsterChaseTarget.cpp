#include "MonsterChaseTarget.h"
#include "DistToNpcSpawn.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "SetNpcAiStateAttack.h"
#include "CanMonsterAttackTarget.h"

void monsterChaseTarget(uint32_t n, Context &ctx)
{
    if (distToNpcSpawn(ctx, n) > NPC_LEASH_RADIUS)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }

    const auto &target = ctx.data.npc.ai.target;
    if (!canMonsterAttackTarget(target.type[n]))
        return;
    const SDL_FRect targetCol = getEntityColAABB(ctx, target.type[n], target.id[n]);

    if (areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    followAStarPathTo(n, ctx, targetCol);
}
