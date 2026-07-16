#include "PetAttack.h"
#include "../monster/RefreshNpcAttackedTimer.h"
#include "AreColBoxesNear.h"
#include "ExecutePetAttack.h"
#include "GetEntityColAABB.h"
#include "NpcMonsterConstants.h"
#include "PetTaunt.h"
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
        setNpcAiStateIdle(ctx, n);
        return;
    }

    const SDL_FRect targetCol = getEntityColAABB(ctx, targetType, targetId);
    if (!areColBoxesNear(ctx, n, targetCol, NPC_ATTACK_REACH))
    {
        setNpcAiStatePursueTarget(ctx, n);
        return;
    }

    if (ctx.data.npc.tauntTimer[n] == 0.0f)
    {
        refreshNpcAttackedTimer(ctx, targetId);
        petTaunt(ctx, n);
    }
    else if (ctx.data.npc.autoAttack.attackTimer[n] == 0.0f)
    {
        refreshNpcAttackedTimer(ctx, targetId);
        executePetAttack(ctx, n, targetType, targetId);
    }
}
