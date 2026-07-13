#include "MonsterPursuingTarget.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "astar/FollowAStarPathTo.h"
#include "SetNpcAiStateReturnToSpawn.h"
#include "SetNpcAiStateAttack.h"
#include "../../../structs/core/EntityType.h"

void monsterPursuingTarget(uint32_t n, Context &ctx)
{
    if (ctx.data.npc.ai.attackedTimer[n] <= 0.0f)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }

    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];
    if (targetType != EntityType::Player && targetType != EntityType::NPC)
    {
        setNpcAiStateReturnToSpawn(n, ctx);
        return;
    }
    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);

    if (areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStateAttack(n, ctx);
        return;
    }

    const int targetNpcIndex = targetType == EntityType::NPC ? targetId : INVALID_ID;
    followAStarPathTo(n, ctx, targetCol, targetNpcIndex);
}
