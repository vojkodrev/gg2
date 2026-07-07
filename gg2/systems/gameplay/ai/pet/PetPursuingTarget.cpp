#include "PetPursuingTarget.h"
#include "AreColBoxesNear.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateIdle.h"
#include "SetNpcAiStateAttack.h"
#include "astar/FollowAStarPathTo.h"
#include "../../../structs/core/EntityType.h"

void petPursuingTarget(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;

    if (target.type[n] == EntityType::None)
    {
        setNpcAiStateIdle(n, ctx);
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
