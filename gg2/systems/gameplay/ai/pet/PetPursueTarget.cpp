#include "PetPursueTarget.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateIdle.h"
#include "SetNpcAiStateAttack.h"
#include "astar/FollowAStarPathTo.h"
#include "../../../structs/core/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"

void petPursueTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];

    if (targetType != EntityType::NPC ||
        !ctx.data.npc.active[targetId] ||
        ctx.data.npc.ai.type[targetId] != NPCAiType::Monster)
    {
        setNpcAiStateIdle(ctx, n);
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
