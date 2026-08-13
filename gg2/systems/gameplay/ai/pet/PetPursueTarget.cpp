#include "PetPursueTarget.h"
#include "../../../structs/core/constants/IndexConstants.h"
#include "GetEntityColAABB.h"
#include "SetPetIdleIfOffScreen.h"
#include "SetNpcAiStateIdle.h"
#include "SetNpcAiStateAttack.h"
#include "astar/FollowAStarPathTo.h"
#include "../../../structs/entity/EntityType.h"
#include "../../../structs/npc/NPCAiType.h"

void petPursueTarget(uint32_t n, Context &ctx)
{
    if (setPetIdleIfOffScreen(ctx, n))
        return;

    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];

    if (targetType != EntityType::NPC ||
        !ctx.data.npc.active[targetId])
    {
        setNpcAiStateIdle(ctx, n);
        return;
    }

    const NPCAiType targetAiType = ctx.data.npc.ai.type[targetId];
    if (targetAiType != NPCAiType::MonsterMelee &&
        targetAiType != NPCAiType::MonsterRanged)
    {
        setNpcAiStateIdle(ctx, n);
        return;
    }

    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);

    const int targetNpcIndex = targetType == EntityType::NPC ? targetId : INVALID_ID;
    const bool goalReached =
        followAStarPathTo(n, ctx, targetCol, targetNpcIndex);
    if (goalReached)
        setNpcAiStateAttack(n, ctx);
}
