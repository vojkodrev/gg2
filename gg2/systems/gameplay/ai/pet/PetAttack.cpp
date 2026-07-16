#include "PetAttack.h"
#include "../monster/RefreshNpcAttackedTimer.h"
#include "AreColBoxesNear.h"
#include "ExecutePetAttack.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "SetNpcAiStateIdle.h"
#include "../SetNpcAiStatePursueTarget.h"
#include "../../../structs/core/EntityType.h"

void petAttack(uint32_t n, Context &ctx)
{
    const auto &target = ctx.data.npc.ai.target;
    const EntityType targetType = target.type[n];
    const int targetId = target.id[n];

    if (targetType == EntityType::NPC && !ctx.data.npc.active[targetId])
    {
        setNpcAiStateIdle(n, ctx);
        return;
    }

    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
    if (!areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStatePursueTarget(n, ctx);
        return;
    }

    if (ctx.data.npc.autoAttack.attackTimer[n] > 0.0f)
        return;

    refreshNpcAttackedTimer(targetId, ctx);
    executePetAttack(n, targetType, targetId, ctx);
}
